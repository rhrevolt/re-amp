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

#include "components/WeaponPhysicsComponent.h"
#include "components/OgreComponent.h"
#include "components/CarOgreComponent.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "Constraints/OgreBulletDynamicsRaycastVehicle.h"

#include "core/StateManager.h"
#include "components/WeaponOgreComponent.h"

#include <OgreSceneQuery.h>


//TODO: What does these do?
#define CUBE_HALF_EXTENTS 0.5
#define GEOMETRY_QUERY_MASK 0

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

int numberOfWeapons = 0;

WeaponPhysicsComponent::WeaponPhysicsComponent(int ID): PhysicsComponent(ID){
};

WeaponPhysicsComponent::~WeaponPhysicsComponent() {

}

bool WeaponPhysicsComponent::tick(FrameData &fd)
{
	direction = carComponent->getChassisNode()->_getDerivedOrientation() * Vector3::UNIT_Z;
	
	//rigidBody->applyForce(direction * weaponSpeed, rigidBody->getCenterOfMassPosition()); 
	if(timer->getMilliseconds()/1000.0f > 10.0)
		parentEntity->destroy();
	return true;
	
}

void WeaponPhysicsComponent::init() {
 }

void WeaponPhysicsComponent::createMissile(CarOgreComponent* source)
{
	carComponent = source;
    WeaponOgreComponent* ogreComp = (WeaponOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
    Ogre::Entity *entity = ogreComp->getEntity();
    SceneManager *mSceneMgr = ogreComp->getSceneMgr();
    assert(entity);
    assert(mSceneMgr);
    
	Vector3 size = Vector3::ZERO;	// size of the box
	direction = source->getNode()->_getDerivedOrientation() * Vector3::UNIT_Z;
	//direction = source->mRootNode->getOrientation() * Vector3::UNIT_Z;
	Vector3 position = (source->getNode()->getPosition());
	
	// Set the speed based on the vehicle speed
	weaponSpeed = abs(carComponent->getSpeed()) + 45.0;

	// we need the bounding box of the box to be able to set the size of the Bullet-box
	AxisAlignedBox boundingB = entity->getBoundingBox();
	size = boundingB.getSize()/2.0;
	//size *= 0.95f;	// Bullet margin is a bit bigger so we need a smaller size
	//entity->setMaterialName("Examples/BumpyMetal");
	SceneNode *node = ogreComp->getNode();
	node->scale(0.5f, 0.5f, 0.5f);	// the cube is too big for us
    //AxisAlignedBox boundingB = node->_getWorldAABB();
    //size = boundingB.getSize();
	size *= 0.025f;						// don't forget to scale down the Bullet-box too
    
	// after that create the Bullet shape with the calculated size
	OgreBulletCollisions::BoxCollisionShape *sceneBoxShape = new OgreBulletCollisions::BoxCollisionShape(size);
	// and the Bullet rigid body
	rigidBody = new OgreBulletDynamics::RigidBody(
			"defaultBoxRigid" + Ogre::StringConverter::toString(numberOfWeapons++), 
			PhysicsManager::getInstance()->getWorld());
	rigidBody->setShape(	node,
				sceneBoxShape,
				0.6f,			// dynamic body restitution
				0.6f,			// dynamic body friction
				50.0f, 			// dynamic bodymass
				position + direction*3,		// starting position of the weapon
				Quaternion(0,0,0,1));// orientation of the weapon			

    rigidBody->getBulletRigidBody()->setCompanionId(numberOfWeapons);
	rigidBody->setLinearVelocity(direction * Vector3(1,0,1) * weaponSpeed); // shooting speed, initial value guess
	timer = new Ogre::Timer();
	timer->reset();
    
    //disable gravity
    //rigidBody->getBulletRigidBody()->setGravity(btVector3(0,-1,0));
    
    //Enable collision callbacks for weapons
    rigidBody->getBulletRigidBody()->setCollisionFlags(rigidBody->getBulletRigidBody()->getCollisionFlags()  | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);	
}
