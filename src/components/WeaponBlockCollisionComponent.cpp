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

#include "components/WeaponBlockCollisionComponent.h"
#include "components/OgreComponent.h"
#include "components/WeaponBlockOgreComponent.h"

#include "Shapes/OgreBulletCollisionsBoxShape.h"

#include "OgreBulletDynamicsWorld.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "core/StateManager.h"
#include "core/PhysicsManager.h"

#include <OgreSceneQuery.h>


#define CUBE_HALF_EXTENTS 0.5
#define GEOMETRY_QUERY_MASK 0

int numberBlocks = 0;

using namespace Ogre;
using namespace OgreBulletCollisions;
using namespace OgreBulletDynamics;

WeaponBlockCollisionComponent::WeaponBlockCollisionComponent(int ID): PhysicsComponent(ID){
};

WeaponBlockCollisionComponent::~WeaponBlockCollisionComponent() {

}

bool WeaponBlockCollisionComponent::tick(FrameData &fd)
{
	//int numManifolds = PhysicsManager::getInstance()->getWorld()->getDispatcher()->getNumManifolds();
	//for(int i=0; i<numManifolds; i++) {               
		//btPersistentManifold* contactManifold = PhysicsManager::getInstance()->getWorld()->getDispatcher()->getManifoldByIndexInternal(i);
//
		//btCollisionObject* objA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		//btCollisionObject* objB = static_cast<btCollisionObject*>(contactManifold->getBody1());
//
		//// this makes things not work according to demo
		////contactManifold->refreshContactPoints(objA->getWorldTransform(),objB->getWorldTransform());
		//int numContacts = contactManifold->getNumContacts();
		//printf("contacts: %d\n",numContacts);
		//if(numContacts==0) continue;
		////you can un-comment out this line, and then all points are removed
		////contactManifold->clearManifold();	
//
		////printf("%lx %lx , ", objA, objB);fflush(stdout);
		//void *movA          = objA->getUserPointer();
		//void *movB          = objB->getUserPointer();
//
        //if(movA==(void*)0x1) {	
                //btConcaveShape *shape=(btConcaveShape*)objA->getCollisionShape();
                //shape->processAllTriangles(&printtri,
                                            //btVector3(-1e30,-1e30,-1e30),
                                            //btVector3(1e30,1e30,1e30));
			
        //} // movA==1
        //if(movB==(void*)0x1) {	
                //btConcaveShape *shape=(btConcaveShape*)objB->getCollisionShape();
                //shape->processAllTriangles(&printtri,
                                            //btVector3(-1e30,-1e30,-1e30),
                                            //btVector3(1e30,1e30,1e30));
			
        //} // movA==1
		//CALL PICKUP WEAPON
		//PhysicsManager::getInstance()->getWorld()->getDispatcher()->clearManifold(contactManifold);

    //}  // for i
	return true;
}

void WeaponBlockCollisionComponent::init() {
	//mWorld->addCollisionObject
	createBlock();
}

void WeaponBlockCollisionComponent::pickupWeapon()
{
}

void WeaponBlockCollisionComponent::createBlock()
{
	WeaponBlockOgreComponent* ogreComp = (WeaponBlockOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
	Ogre::SceneNode* weaponBlockRootNode = ogreComp->getNode();

	assert(weaponBlockRootNode);

	BoxCollisionShape* blockShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));
	//BoxCollisionShape* chassisShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,2.1f));

	mBox = new RigidBody("boxPhysics" + Ogre::StringConverter::toString(numberBlocks++), PhysicsManager::getInstance()->getWorld());

	Ogre::Vector3 initialPosition = Ogre::Vector3(parentEntity->getProperties()->get<float>("<xmlattr>.pos_x"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_z"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_y"));
	mBox->setShape(weaponBlockRootNode, blockShape, .8, .8, 0, initialPosition, Quaternion::IDENTITY);
	mBox->setDamping(.2, .2);

	// set up a pointer for collision detection
	//mBox->setUserPointer((void*) 0x2);

	mBox->disableDeactivation ();
}

