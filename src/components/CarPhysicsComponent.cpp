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

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

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

int numPhysicsInstanced = 0;

CarPhysicsComponent::CarPhysicsComponent(int ID): PhysicsComponent(ID), 
	gAcceleration(0.0f),
	gMaxEngineForce(0.0f),
	gEngineDecayRate(0.0f),
	gBrakingIncrement(0.0f),
	gSteeringIncrement(0.0f),
	gSteeringClamp(0.0f),
	gSteeringDecayRate(0.0f),
	gWheelRadius(0.0f),
	gWheelWidth(0.0f),
	gWheelFriction(0.0f),
	gSuspensionStiffness(0.0f),
	gSuspensionDamping(0.0f),
	gSuspensionCompression(0.0f),
	gRollInfluence(0.0f),
	gSuspensionRestLength(0.0f),
	gMaxSuspensionTravelCm(0.0f),
	gFrictionSlip(0.0f),
	gEngineZeroThreshold(0.0f),
	gSteeringZeroThreshold(0.0f)
{
};

CarPhysicsComponent::~CarPhysicsComponent() {

}

bool CarPhysicsComponent::tick(FrameData &fd)
{
	//printf("ticking physics..\n");
	// Decay the engine force
	if (mEngineForce > 0) {
		mEngineForce = std::max(0.0f, mEngineForce - gEngineDecayRate);
	} else if (mEngineForce < 0) {
		mEngineForce = std::min(0.0f, mEngineForce + gEngineDecayRate);
	}

	// Check if the engine force is close enough to zero
	if (abs(mEngineForce) < gEngineZeroThreshold) {
		mEngineForce = 0;
	}

	// Decay the steering 
	if (mSteering > 0) {
		mSteering = std::max(0.0f, mSteering - gSteeringDecayRate);
	} else if (mSteering < 0) {
		mSteering = std::min(0.0f, mSteering + gSteeringDecayRate);
	}
	printf("msteering: %f\n", mSteering); 
	// Check if the steering force is close enough to zero
	if (abs(mSteering) < gSteeringZeroThreshold) {
		mSteering = 0;
	}

	//printf("%f\n", fd.timeSinceLastFrame);

	// apply steering and engine force on wheels
	for (int i = mWheelsEngine[0]; i < mWheelsEngineCount; i++)
	{
		// Try to scale the force
		if (fd.timeSinceLastFrame > 0)
			mVehicle->applyEngineForce(mEngineForce, mWheelsEngine[i]);
		else
			mVehicle->applyEngineForce(mEngineForce, mWheelsEngine[i]);
	}

	for (int i = mWheelsSteerable[0]; i < mWheelsSteerableCount; i++)
	{
		if (i < 2) {
			if (fd.timeSinceLastFrame > 0)
				mVehicle->setSteeringValue (mSteering, mWheelsSteerable[i]);
			else
				mVehicle->setSteeringValue(mSteering, mWheelsSteerable[i]);
		} else {
			if (fd.timeSinceLastFrame > 0)
				mVehicle->setSteeringValue (-mSteering, mWheelsSteerable[i]);
			else
				mVehicle->setSteeringValue(-mSteering, mWheelsSteerable[i]);
		}
	}

	// Fire an event with the vehicle speed
	signal_speedUpdated(mVehicle->getBulletVehicle()->getCurrentSpeedKmHour());
	return true;
}

float CarPhysicsComponent::getCurrentSpeed() {
	return mVehicle->getBulletVehicle()->getCurrentSpeedKmHour();
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

void CarPhysicsComponent::init()
{
	// Load physics constants
	loadPhysicsConstants("car_config.xml");

	//Construct the physics basis for the vehicle
	const Ogre::Vector3 chassisShift(0, 1.0f, 0);
	Ogre::Vector3 initial;
	initial.x = parentEntity->getProperties()->get<float>("<xmlattr>.pos_x");
	initial.y = parentEntity->getProperties()->get<float>("<xmlattr>.pos_y");
	initial.z = 0;
	createVehicle(chassisShift, initial);

	mEngineForce = 0;
	mSteering = 0;
}

void CarPhysicsComponent::loadPhysicsConstants(const std::string &filename)
{
	using boost::property_tree::ptree;
	
	ptree pTree;
	// Load from XML
	read_xml(filename, pTree);
	gAcceleration = pTree.get<float>("physics.gAcceleration");
	gMaxEngineForce = pTree.get<float>("physics.gMaxEngineForce");
	gEngineDecayRate = pTree.get<float>("physics.gEngineDecayRate");
	gBrakingIncrement = pTree.get<float>("physics.gBrakingIncrement");
	gSteeringIncrement = pTree.get<float>("physics.gSteeringIncrement");
	gSteeringClamp = pTree.get<float>("physics.gSteeringClamp");
	gSteeringDecayRate = pTree.get<float>("physics.gSteeringDecayRate");
	gWheelRadius = pTree.get<float>("physics.gWheelRadius");
	gWheelWidth = pTree.get<float>("physics.gWheelWidth");
	gWheelFriction = pTree.get<float>("physics.gWheelFriction");
	gSuspensionStiffness = pTree.get<float>("physics.gSuspensionStiffness");
	gSuspensionDamping = pTree.get<float>("physics.gSuspensionDamping");
	gSuspensionCompression = pTree.get<float>("physics.gSuspensionCompression");
	gRollInfluence = pTree.get<float>("physics.gRollInfluence");
	gSuspensionRestLength = pTree.get<float>("physics.gSuspensionRestLength");
	gMaxSuspensionTravelCm = pTree.get<float>("physics.gMaxSuspensionTravel");
	gFrictionSlip = pTree.get<float>("physics.gFrictionSlip");
	gEngineZeroThreshold = pTree.get<float>("physics.gEngineZeroThreshold");
	gSteeringZeroThreshold = pTree.get<float>("physics.gSteeringZeroThreshold");
	gVehicleMass = pTree.get<float>("physics.gVehicleMass");

	// Setup the drive and steering mechanism
	for (int i = 0; i < 4; i++)
	{
		mWheelsEngine[i] = 0;
		mWheelsSteerable[i] = 0;
	}

	switch (pTree.get<int>("physics.gEngineForceConfiguration")) {
		case 0: // front wheel drive
			mWheelsEngineCount = 2;
			mWheelsEngine[0] = 0;
			mWheelsEngine[1] = 1;
			break;
		case 1: // rear wheel drive
			mWheelsEngineCount = 2;
			mWheelsEngine[0] = 2;
			mWheelsEngine[1] = 3;
			break;
		case 2: // all wheel drive
			mWheelsEngineCount = 4;
			mWheelsEngine[0] = 0;
			mWheelsEngine[1] = 1;
			mWheelsEngine[2] = 2;
			mWheelsEngine[3] = 3;
			break;
	}

	switch (pTree.get<int>("physics.gSteeringConfiguration")) {
		case 0: // front wheel steering
			mWheelsSteerableCount = 2;
			mWheelsSteerable[0] = 0;
			mWheelsSteerable[1] = 1;
			break;
		case 1: // all-wheel steering
			mWheelsSteerableCount = 4;
			mWheelsSteerable[0] = 0;
			mWheelsSteerable[1] = 1;
			mWheelsSteerable[2] = 2;
			mWheelsSteerable[3] = 3;
			break;
	}
}

void CarPhysicsComponent::createVehicle( Ogre::Vector3 chassisShift, Ogre::Vector3 initialPosition )
{
	//TODO: Get this value from Ogre Component
	float connectionHeight = 0.7f;

	CarOgreComponent* ogreComp = (CarOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
	Ogre::SceneNode* carRootNode = ogreComp->getNode();

	assert(carRootNode);

	BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	CompoundCollisionShape* compound = new CompoundCollisionShape();
	compound->addChildShape(chassisShape, chassisShift);

	mCarChassis = new WheeledRigidBody("carChassisPhysics" + Ogre::StringConverter::toString(numPhysicsInstanced++), PhysicsManager::getInstance()->getWorld());

	mCarChassis->setShape(carRootNode, compound, 0.8, 0.8, gVehicleMass, initialPosition, Quaternion::IDENTITY);
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
