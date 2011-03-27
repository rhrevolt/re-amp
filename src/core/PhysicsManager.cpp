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

#include "core/PhysicsManager.h"
#include "ExampleApplication.h"
 #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
 #include "../res/resource.h"
 #endif
 #include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet

PhysicsManager::PhysicsManager ()
 	{
		//TODO: Change if necessary
		AxisAlignedBox* bounds = NULL;
		Vector3 *gravityVector = new Vector3(0, -1, 0);
		 
 		mNumEntitiesInstanced = 0; // how many shapes are created
 		mSceneMgr = StateManager::getCurrentState()->getSceneMgr();
		 
 		// Start Bullet
 		mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, *bounds, *gravityVector);
 
 	        // add Debug info display tool
 		debugDrawer = new OgreBulletCollisions::DebugDrawer();
 		debugDrawer->setDrawWireframe(true);	// we want to see the Bullet containers
 
 		mWorld->setDebugDrawer(debugDrawer);
 		mWorld->setShowDebugShapes(true);		// enable it if you want to see the Bullet containers
 		SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
 		node->attachObject(static_cast <SimpleRenderable *> (debugDrawer));
    }


PhysicsManager::~PhysicsManager (void)
{
	std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
	while (mBodies.end() != itBody)
	{   
		delete *itBody; 
		++itBody;
	}	
	
	// OgreBullet physic delete - Shapes
	std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
	while (mShapes.end() != itShape)
	{   
		delete *itShape; 
		++itShape;
	}
	
	mBodies.clear();
	mShapes.clear();
	delete mWorld->getDebugDrawer();
	mWorld->setDebugDrawer(0);
	delete mWorld;
}

bool tick(FrameData &fd) 
{
	for(int i = 0; i < addPhysicsList.size(); i++)
		addPhysicsList[i]->stepSimulation(fd.timeSinceLastFrame);

	mWorld->stepSimulation(fd.timeSinceLastFrame);	// update Bullet Physics animation

	return ret;
}
	
bool registerComponent(PhysicsComponent* component)
{		
	componentList.push_back(component);
}

 /* bool PhysicsManager::frameStarted(const FrameEvent& evt)
 	{
		for(int i = 0; i < addPhysicsList.size(); i++)
			addPhysicsList[i]->stepSimulation(evt.timeSinceLastFrame);
			
 		bool ret = ExampleFrameListener::frameStarted(evt);
 
 		mWorld->stepSimulation(evt.timeSinceLastFrame);	// update Bullet Physics animation
 
 		return ret;
 	}
 
 bool PhysicsManager::frameEnded(const FrameEvent& evt)
 	{
 		bool ret = ExampleFrameListener::frameEnded(evt);
 
 		mWorld->stepSimulation(evt.timeSinceLastFrame);	// update Bullet Physics animation
 
 		return ret;
 	}
*/	

OgreBulletDynamics::DynamicsWorld* PhysicsManager::getWorld(){
	return mWorld;
}

