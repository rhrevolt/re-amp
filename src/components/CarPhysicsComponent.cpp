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
#include <algorithm>

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
#define CUBE_HALF_EXTENTS 1
#define GEOMETRY_QUERY_MASK 0

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

CarPhysicsComponent::CarPhysicsComponent(int ID): PhysicsComponent(ID){
	gAcceleration = 0.1f;
	gMaxEngineForce = 10.0f;
	gEngineDecayRate = 3.0f;
	gBrakingIncrement = 0.800f;

	gSteeringIncrement = 0.02f;
	gSteeringClamp = 0.1f;
	gSteeringDecayRate = 0.03f;

	gWheelRadius = 0.5f;
	gWheelWidth = 0.4f;

	gWheelFriction = 1e15f;//1000;//1e30f;
	gSuspensionStiffness = 20.f;
	gSuspensionDamping = 2.3f;
	gSuspensionCompression = 4.4f;
	gRollInfluence = 0.3f;//1.0f;
	gSuspensionRestLength = 0.6;
	gMaxSuspensionTravelCm = 500.0;
	gFrictionSlip = 10.5;
};

CarPhysicsComponent::~CarPhysicsComponent() {

}

bool CarPhysicsComponent::tick(FrameData &fd)
{
	printf("ticking physics..\n");
	// Decay the engine force
	if (mEngineForce > 0) {
		mEngineForce = std::max(0.0f, mEngineForce - gEngineDecayRate);
	} else if (mEngineForce < 0) {
		mEngineForce = std::min(0.0f, mEngineForce + gEngineDecayRate);
	}

	// Decay the steering 
	if (mSteering > 0) {
		mSteering = std::max(0.0f, mSteering - gSteeringDecayRate);
	} else if (mSteering < 0) {
		mSteering = std::min(0.0f, mSteering + gSteeringDecayRate);
	}

	printf("%f\n", fd.timeSinceLastFrame);

	// apply steering and engine force on wheels
	for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++)
	{
		// Try to scale the force
		if (fd.timeSinceLastFrame > 0)
			mVehicle->applyEngineForce(mEngineForce / fd.timeSinceLastFrame, mWheelsEngine[i]);
		else
			mVehicle->applyEngineForce(mEngineForce, mWheelsEngine[i]);
	}

	for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	{
		if (i < 2) {
			if (fd.timeSinceLastFrame > 0)
				mVehicle->setSteeringValue (mSteering / fd.timeSinceLastFrame, mWheelsSteerable[i]);
			else
				mVehicle->setSteeringValue(mSteering, mWheelsSteerable[i]);
		} else {
			if (fd.timeSinceLastFrame > 0)
				mVehicle->setSteeringValue (-mSteering / fd.timeSinceLastFrame, mWheelsSteerable[i]);
			else
				mVehicle->setSteeringValue(-mSteering, mWheelsSteerable[i]);
		}
	}

	return true;
}

void CarPhysicsComponent::handleVector(Ogre::Vector2 bufferedVector)
{
	// Check if the x (steering) component of the vector is non-zero
	if (bufferedVector.x != 0)
	{
		// Apply the x vector (turning)
		if (bufferedVector.x > 0)
			mSteering = std::min(gSteeringClamp, mSteering + gSteeringIncrement + gSteeringDecayRate);
		else
			mSteering = std::max(-gSteeringClamp, mSteering - gSteeringIncrement - gSteeringDecayRate);
	}

	// Check if the y (acceleration) component of the vector is non-zero
	if (bufferedVector.y != 0)
	{
		float vehicleSpeed =  mVehicle->getBulletVehicle()->getCurrentSpeedKmHour();
		// Check if we're braking 
		if ((bufferedVector.y > 0 && vehicleSpeed < 0) || (bufferedVector.y < 0 && vehicleSpeed > 0)) {
			// Apply a braking force
			if (vehicleSpeed > 0)
				mEngineForce = std::max(-gMaxEngineForce, mEngineForce - gBrakingIncrement - gEngineDecayRate);
			else
				mEngineForce = std::min(gMaxEngineForce, mEngineForce + gBrakingIncrement + gEngineDecayRate);
		} else {
			// Apply a normal acceleration
			if (bufferedVector.y > 0)
				mEngineForce = std::min(gMaxEngineForce, mEngineForce + gAcceleration + gEngineDecayRate);
			else
				mEngineForce = std::max(-gMaxEngineForce, mEngineForce - gAcceleration - gEngineDecayRate);
		}

	}
}

void CarPhysicsComponent::init() {
	// Get the input manager
	mInputManager = InputManager::getInstance();

	// Connect our events with the InputManager
	printf(mInputManager->signal_acceleration.connect(boost::bind(&CarPhysicsComponent::handleVector, this, _1)).connected() ? "connected\n " : "disconnected\n");
	//Construct the physics basis for the vehicle
	const Ogre::Vector3 chassisShift(0, 1.0f, 0);
	createVehicle(chassisShift);

	for (int i = 0; i < 4; i++)
	{
		mWheelsEngine[i] = 0;
		mWheelsSteerable[i] = 0;
	}
	mWheelsEngineCount = 4;
	mWheelsEngine[0] = 0;
	mWheelsEngine[1] = 1;
	mWheelsEngine[2] = 2;
	mWheelsEngine[3] = 3;

	mWheelsSteerableCount = 4;
	mWheelsSteerable[0] = 0;
	mWheelsSteerable[1] = 1;
	mWheelsSteerable[2] = 2;
	mWheelsSteerable[3] = 3;

	mWheelEngineStyle = 0;
	mWheelSteeringStyle = 0;

	mSteeringLeft = false;
	mSteeringRight = false;

	mEngineForce = 0;
	mSteering = 0;
}

void CarPhysicsComponent::createVehicle( Ogre::Vector3 chassisShift )
{
	//TODO: Get this value from Ogre Component
	float connectionHeight = 0.7f;

	CarOgreComponent* ogreComp = (CarOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
	Ogre::SceneNode* carRootNode = ogreComp->getNode();

	assert(carRootNode);

	BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	CompoundCollisionShape* compound = new CompoundCollisionShape();
	compound->addChildShape(chassisShape, chassisShift);

	mCarChassis = new WheeledRigidBody("carChassisPhysics", PhysicsManager::getInstance()->getWorld());

	mCarChassis->setShape(carRootNode, compound, 0.8, 0.8, 3200, Ogre::Vector3(0, 3, 0), Quaternion::IDENTITY);
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

	/* Now construct our wheels */
	SceneNode** mWheelNodes = ogreComp->getWheelNodes();

	{
		int rightIndex = 0;
		int upIndex = 1;
		int forwardIndex = 2;

		mVehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

		Ogre::Vector3 wheelDirectionCS0(0,-1,0);
		Ogre::Vector3 wheelAxleCS(-1,0,0);

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
	mVehicle->setWheelsAttached();
}
