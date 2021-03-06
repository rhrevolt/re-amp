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
#include "components/WeaponPhysicsComponent.h"

class CarPhysicsComponent: public PhysicsComponent
{
	public:
		CarPhysicsComponent(int ID);
		~CarPhysicsComponent();
		virtual bool tick(FrameData &fd);
		void createVehicle(Ogre::Vector3 chassisShift, Ogre::Vector3 initial);
		virtual void init();
		virtual void handleVector(Ogre::Vector2 vec);

		OgreBulletDynamics::RaycastVehicle* getVehicle() {return mVehicle;};

		virtual float getCurrentSpeed();
		
		virtual void applyFirework(WeaponPhysicsComponent* weap);
		
		// BOOST signals
		/*
		   signal_speedUpdated - fires when the speed of the vehicle 
		   changed
		   - one param - the new speed (in km/h)
		 */
		boost::signal<void (float speed)> signal_speedUpdated;

		/*
		   signal_epxlosion - fires when the missile collides with the vehicle 
		   params - position and direction
		 */
		boost::signal<void (Ogre::Vector3 pos, Ogre::Vector3 dir)> signal_explosion;
		
	protected:
		void loadPhysicsConstants(const std::string &filename);
		
	private:
		float	gMaxEngineForce;
		float	gBrakingIncrement;
		float	gSteeringIncrement; 
		float	gSteeringClamp ;
		float	gSteeringDecayRate;

		float   gAcceleration;
		float	gWheelRadius ;
		float	gWheelWidth ;
		float	gEngineDecayRate;

		float	gWheelFriction;//1000;//1e30f;
		float	gSuspensionStiffness;
		float	gSuspensionDamping;
		float	gSuspensionCompression;
		float	gRollInfluence;//1.0f;
		float   gSuspensionRestLength;
		float   gMaxSuspensionTravelCm;
		float   gFrictionSlip;
		float	gEngineZeroThreshold;
		float	gSteeringZeroThreshold;

		float	gVehicleMass;
		float	gVehicleSpeedCap;
		float	gVehicleSpeedCapForce;
		float	gReverseSpeedCap;
		float	gReverseSpeedCapForce;
		float	gReverseAcceleration;

		OgreBulletDynamics::WheeledRigidBody        *mCarChassis;
		OgreBulletDynamics::VehicleTuning	        *mTuning;
		OgreBulletDynamics::VehicleRayCaster	    *mVehicleRayCaster;
		OgreBulletDynamics::RaycastVehicle	        *mVehicle;

		Ogre::Entity    *mWheels[4];
		Ogre::SceneNode *mWheelNodes[4];

		int mWheelsEngine[4];
		int mWheelsEngineCount;
		int mWheelsSteerable[4];
		int mWheelsSteerableCount;

		float mEngineForce;
		float mSteering;

};

#endif // _CARPHYSICSCOMPONENT_H_
