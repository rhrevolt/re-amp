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
#include "OgreBulletCollisionsWorld.h"
#include "OgreBulletCollisionsObject.h"
#include "Utils/OgreBulletConverter.h"
#include "OgreBulletDynamicsRigidBody.h"
#include "Debug/OgreBulletCollisionsDebugDrawer.h"

#include "core/StateManager.h"

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

	return true;
}

void WeaponBlockCollisionComponent::init() {
	//cWorld = PhysicsManager::getInstance()->getCollisionWorld();
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

	BoxCollisionShape* blockShape = new BoxCollisionShape(Ogre::Vector3(1.f,0.75f,1.f));

	mBox = new RigidBody("boxPhysics" + Ogre::StringConverter::toString(numberBlocks++), PhysicsManager::getInstance()->getWorld());

	Ogre::Vector3 initialPosition = Ogre::Vector3(parentEntity->getProperties()->get<float>("<xmlattr>.pos_x"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_z"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_y"));

	mBox->setShape(weaponBlockRootNode, blockShape, .8, .8, 0, initialPosition, Quaternion::IDENTITY);
	mBox->setDamping(.2, .2);

	mBox->disableDeactivation ();

	// Set up callback function for collision
	mBox->getBulletRigidBody()->setCollisionFlags(mBox->getBulletRigidBody()->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	
}

