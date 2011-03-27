/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * re-amp
 * Copyright (C)  2011 <>
 * 
 * re-amp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * re-amp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#include <stdio.h>
//#include <Ogre.h>

// Our includes
#include "core/EventManager.h"
#include "core/StateManager.h"
#include "components/PhysicsComponent.h"
#include <vector>
#include "core/Singleton.h"
#include "OgreBulletDynamicsRigidBody.h"	// for OgreBullet


class PhysicsManager: public Singleton<PhysicsManager>
{
friend class Singleton<PhysicsManager>;
public:
	PhysicsManager ();
	~PhysicsManager (void);

	bool tick(FrameData &fd);
	bool registerComponent(PhysicsComponent* component);
	
	OgreBulletDynamics::DynamicsWorld* getWorld();

	
protected:
	;

private:
	Ogre::SceneManager* mSceneMgr; 
 	OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
 	OgreBulletCollisions::DebugDrawer *debugDrawer;
 	int mNumEntitiesInstanced;

	std::list<PhysicsComponent*> componentList; 
 	std::deque<OgreBulletDynamics::RigidBody *>         mBodies;
 	std::deque<OgreBulletCollisions::CollisionShape *>  mShapes;

	bool running; 

};

#endif // _PHYSICS_MANAGER_H_
