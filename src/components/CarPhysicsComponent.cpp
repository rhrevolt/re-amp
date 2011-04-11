/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ReAmp
 * Copyright (C)  2011 <>
 *
 * ReAmp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReAmp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include "components/CarPhysicsComponent.h"
#include "components/OgreComponent.h"
#include "components/CarOgreComponent.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

#include "core/StateManager.h"

#include <OgreSceneQuery.h>


//TODO: What does these do?
#define CUBE_HALF_EXTENTS 0.5
#define GEOMETRY_QUERY_MASK 0

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

CarPhysicsComponent::CarPhysicsComponent(int ID): PhysicsComponent(ID){
	gAcceleration = 5.0f;
	gMaxEngineForce = 3000.f;

	gSteeringIncrement = 0.04f;
	gSteeringClamp = 0.8f;

	gWheelRadius = 0.5f;
	gWheelWidth = 0.4f;

	gWheelFriction = 1e30f;//1000;//1e30f;
	gSuspensionStiffness = 20.f;
	gSuspensionDamping = 2.3f;
	gSuspensionCompression = 4.4f;
	gRollInfluence = 0.1f;//1.0f;
	gSuspensionRestLength = 0.6;
	gMaxSuspensionTravelCm = 500.0;
	gFrictionSlip = 10.5;
};

CarPhysicsComponent::~CarPhysicsComponent() {

}

bool CarPhysicsComponent::tick(FrameData &fd)
{
	if (mInputManager->KEY_ACCEL) {
		mEngineForce += gAcceleration;
		if (mEngineForce > gMaxEngineForce) {
			mEngineForce = gMaxEngineForce;
		}
	}

	if (mInputManager->KEY_BRAKE) {
		mEngineForce -= gAcceleration;
		if (mEngineForce < -gMaxEngineForce) {
			mEngineForce = -gMaxEngineForce;
		}
	}

	if (mInputManager->KEY_LEFT)
	{
		mSteering += gSteeringIncrement;
		if (mSteering > gSteeringClamp)
			mSteering = gSteeringClamp;
	}
	else if (mInputManager->KEY_RIGHT)
	{
		mSteering -= gSteeringIncrement;
		if (mSteering < -gSteeringClamp)
			mSteering = -gSteeringClamp;
	}

	// apply steering and engine force on wheels
	for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++)
	{
		mVehicle->applyEngineForce(mEngineForce, mWheelsEngine[i]);
	}

	for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	{
		if (i < 2)
			mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
		else
			mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
	}

	return true;
}

void CarPhysicsComponent::init() {
	// Get the input manager
	mInputManager = InputManager::getInstance();

	//Construct the physics basis for the vehicle
	const Ogre::Vector3 chassisShift(0, 1.0, 0);
	createVehicle(NULL, chassisShift, NULL);
	
	for (int i = 0; i < 4; i++)
	{
		mWheelsEngine[i] = 0;
		mWheelsSteerable[i] = 0;
	}
	mWheelsEngineCount = 2;
	mWheelsEngine[0] = 0;
	mWheelsEngine[1] = 1;
	mWheelsEngine[2] = 2;
	mWheelsEngine[3] = 3;

	mWheelsSteerableCount = 2;
	mWheelsSteerable[0] = 0;
	mWheelsSteerable[1] = 1;
	//mWheelsSteerable[2] = 2;
	//mWheelsSteerable[3] = 3;

	mWheelEngineStyle = 0;
	mWheelSteeringStyle = 0;

	mSteeringLeft = false;
	mSteeringRight = false;

	mEngineForce = 0;
	mSteering = 0;
}

void CarPhysicsComponent::createVehicle(Ogre::SceneNode *carNode, 
                                        Ogre::Vector3 chassisShift, 
                                        Ogre::SceneNode *mWheelNodes[4])
{
	//TODO: Get this value from Ogre Component
	float connectionHeight = 0.7f;

	CarOgreComponent* ogre = (CarOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
	Ogre::SceneNode* node = ogre->getNode();

	BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	CompoundCollisionShape* compound = new CompoundCollisionShape();
	compound->addChildShape(chassisShape, chassisShift);
	
	mCarChassis = new WheeledRigidBody("carChassis", PhysicsManager::getInstance()->getWorld());

	mCarChassis->setShape(ogre->carNode, compound, 0.6, 0.6, 800, Ogre::Vector3(0, 3, 0), Quaternion::IDENTITY);
	mCarChassis->setDamping(0.2, 0.2);

	mCarChassis->disableDeactivation ();
	mTuning = new VehicleTuning(
			gSuspensionStiffness,
			gSuspensionCompression,
			gSuspensionDamping,
			gMaxSuspensionTravelCm,
			gFrictionSlip);

	mVehicleRayCaster = new VehicleRayCaster(PhysicsManager::getInstance()->getWorld());
	mVehicle = new RaycastVehicle(mCarChassis, mTuning, mVehicleRayCaster);

	/*
	{
		int rightIndex = 0;
		int upIndex = 1;
		int forwardIndex = 2;

		mVehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

		Ogre::Vector3 wheelDirectionCS0(0,-1,0);
		Ogre::Vector3 wheelAxleCS(-1,0,0);

		for (size_t i = 0; i < 4; i++)
		{
			mWheels[i] = mSceneMgr->createEntity(
					"wheel" + StringConverter::toString(mNumEntitiesInstanced++),
					"wheel.mesh");

			mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
#if (OGRE_VERSION < ((1 << 16) | (5 << 8) | 0)) // only applicable before shoggoth (1.5.0)
			mWheels[i]->setNormaliseNormals(true);
#endif
			mWheels[i]->setCastShadows(true);

			mWheelNodes[i] = mSceneMgr->getRootSceneNode ()->createChildSceneNode ();
			mWheelNodes[i]->attachObject (mWheels[i]);

		}

		{
			bool isFrontWheel = true;

			Ogre::Vector3 connectionPointCS0 (
					CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
					connectionHeight,
					2*CUBE_HALF_EXTENTS-gWheelRadius);


	mVehicle->addWheel(
			mWheelNodes[0],
			connectionPointCS0,
			wheelDirectionCS0,
			wheelAxleCS,
			gSuspensionRestLength,
			gWheelRadius,
			isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3(
			-CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
			connectionHeight,
			2*CUBE_HALF_EXTENTS-gWheelRadius);


	mVehicle->addWheel(
			mWheelNodes[1],
			connectionPointCS0,
			wheelDirectionCS0,
			wheelAxleCS,
			gSuspensionRestLength,
			gWheelRadius,
			isFrontWheel, gWheelFriction, gRollInfluence);


	connectionPointCS0 = Ogre::Vector3(
			-CUBE_HALF_EXTENTS+(0.3*gWheelWidth),
			connectionHeight,
			-2*CUBE_HALF_EXTENTS+gWheelRadius);

	isFrontWheel = false;
	mVehicle->addWheel(
			mWheelNodes[2],
			connectionPointCS0,
			wheelDirectionCS0,
			wheelAxleCS,
			gSuspensionRestLength,
			gWheelRadius,
			isFrontWheel, gWheelFriction, gRollInfluence);

	connectionPointCS0 = Ogre::Vector3(
			CUBE_HALF_EXTENTS-(0.3*gWheelWidth),
			connectionHeight,
			-2*CUBE_HALF_EXTENTS+gWheelRadius);

	mVehicle->addWheel(
			mWheelNodes[3],
			connectionPointCS0,
			wheelDirectionCS0,
			wheelAxleCS,
			gSuspensionRestLength,
			gWheelRadius,
			isFrontWheel, gWheelFriction, gRollInfluence);
	}
	}
*/
}
