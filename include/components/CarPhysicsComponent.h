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

#ifndef _CARPHYSICSCOMPONENT_H_
#define _CARPHYSICSCOMPONENT_H_

#include <Ogre.h>
#include "components/PhysicsComponent.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"

class CarPhysicsComponent: public PhysicsComponent
{
public:
	CarPhysicsComponent(int ID);
	~CarPhysicsComponent();
	virtual bool tick(FrameData &fd);
	void init();
	void createVehicle(Ogre::SceneNode *carNode, Ogre::Vector3 chassisShift, Ogre::SceneNode *mWheelNodes[4]);

protected:

private:
	float	gMaxEngineForce;

    float	gSteeringIncrement; 
	float	gSteeringClamp ;
	
	float gAcceleration;
	float	gWheelRadius ;
	float	gWheelWidth ;

	float	gWheelFriction;//1000;//1e30f;
	float	gSuspensionStiffness;
	float	gSuspensionDamping;
	float	gSuspensionCompression;
    float	gRollInfluence;//1.0f;
	float   gSuspensionRestLength;
	float   gMaxSuspensionTravelCm;
	float   gFrictionSlip;
	
	OgreBulletDynamics::WheeledRigidBody        *mCarChassis;
    OgreBulletDynamics::VehicleTuning	        *mTuning;
    OgreBulletDynamics::VehicleRayCaster	    *mVehicleRayCaster;
    OgreBulletDynamics::RaycastVehicle	        *mVehicle;

    int mWheelsEngine[4];
    int mWheelsEngineCount;
    int mWheelsSteerable[4];
    int mWheelsSteerableCount;

    float mEngineForce;
    float mSteering;

    int mWheelEngineStyle;
    int mWheelSteeringStyle;


    bool mSteeringLeft;
    bool mSteeringRight;
	InputManager* mInputManager;
};

#endif // _CARPHYSICSCOMPONENT_H_
