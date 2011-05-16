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

#include <boost/foreach.hpp>

#include "core/PhysicsManager.h"
#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include <OgreAxisAlignedBox.h>

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

PhysicsManager::PhysicsManager() : initialized(false)
{
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
	delete mWorld;
}

void PhysicsManager::init()
{
	//TODO: Change if necessary
	AxisAlignedBox* bounds = new AxisAlignedBox();
	Vector3 *gravityVector = new Vector3(0, -9.81, 0);

	mNumEntitiesInstanced = 0; // how many shapes are created
	mSceneMgr = StateManager::getCurrentState()->getSceneMgr();

	// Start Bullet
	assert(bounds != NULL);
	assert(mSceneMgr != NULL);

	mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, *bounds, *gravityVector);
	// enable if you want to see bounding boxes
	mWorld->setShowDebugShapes(true);

	// Setup the tick callback
	mWorld->getBulletDynamicsWorld()->setInternalTickCallback(&PhysicsManager::btTickCallbackWrapper);

	initialized = true;

	/* for collision world if necessary

	cWorld = new OgreBulletCollisions::CollisionsWorld(mSceneMgr, *bounds, false, true);
	cWorld->setShowDebugContactPoints(true);
	*/
}

bool PhysicsManager::tick(FrameData &fd)
{
	if (initialized) {
		mWorld->stepSimulation(fd.timeSinceLastFrame);	// update Bullet Physics animation
	}
	return true;
}

void PhysicsManager::btTickCallbackWrapper(btDynamicsWorld* world, btScalar timeStep)
{
	PhysicsManager::getInstance()->btTickCallback(world, timeStep);
}

void PhysicsManager::btTickCallback(btDynamicsWorld* world, btScalar timeStep)
{
	FrameData fd;
	fd.timeSinceLastFrame = timeStep;
	BOOST_FOREACH(PhysicsComponent* comp, componentList) {
		comp->tick(fd);
	}
}

bool PhysicsManager::registerComponent(PhysicsComponent* component)
{
	componentList.push_back(component);
	return true;
}

OgreBulletDynamics::DynamicsWorld* PhysicsManager::getWorld(){
	return mWorld;
}

/* 
OgreBulletCollisions::CollisionsWorld* PhysicsManager::getCollisionWorld(){
	return cWorld;
}
*/

std::deque<OgreBulletDynamics::RigidBody *> * PhysicsManager::getBodies(){
	return &mBodies;
}

std::deque<OgreBulletCollisions::CollisionShape *> * PhysicsManager::getShapes(){
	return &mShapes;
}

