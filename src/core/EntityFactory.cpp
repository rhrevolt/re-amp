/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ReAmp
 * Copyright (C)  2011 ReAmp Contributors
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

#include <string>
#include "core/EntityFactory.h"
#include "core/GameEntity.h"
#include "core/PhysicsManager.h"
#include "core/GameComponent.h"

#include "components/InputComponent.h"
#include "components/CarOgreComponent.h"
#include "components/CarPhysicsComponent.h"
#include "components/TerrainOgreComponent.h"
#include "components/PhysicsComponent.h"
#include "components/CameraComponent.h"
#include "components/CarSoundComponent.h"
#include "components/WeaponOgreComponent.h"
#include "components/WeaponPhysicsComponent.h"
#include "components/WeaponSoundComponent.h"
#include "components/WeaponBlockOgreComponent.h"
#include "components/WeaponBlockCollisionComponent.h"
#include "components/HUDComponent.h"

#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"

GameEntity* EntityFactory::create(std::string name, boost::property_tree::ptree* pTree)
{
	GameEntity* ent = new (GameEntity);
	ent->setPropertyTree(pTree);
	// TODO: Perhaps this should be generated from a file?
	if (name == "playerCar") {
		ent->addComponent((GameComponent*) new CarOgreComponent(0));
		ent->addComponent((GameComponent*) new CarPhysicsComponent(0));
		ent->addComponent((GameComponent*) new CameraComponent(0));
		ent->addComponent((GameComponent*) new CarSoundComponent(0));
		ent->addComponent((GameComponent*) new InputComponent(0));
		ent->addComponent((GameComponent*) new HUDComponent(0));
		ent->initializeComponents();

	} else if (name == "car") {
		ent->addComponent((GameComponent*) new CarOgreComponent(0));
		ent->addComponent((GameComponent*) new CarPhysicsComponent(0));
		ent->addComponent((GameComponent*) new CarSoundComponent(0));
		ent->initializeComponents();
		Ogre::Vector3 vec(40,40,0);
		((OgreComponent*)ent->getComponent(COMPONENT_OGRE))->setInitialPosition(vec);

	} else if (name == "weapon block") {
		WeaponBlockOgreComponent* blockOgre = new WeaponBlockOgreComponent(0);
		ent->addComponent((GameComponent*) blockOgre);
		WeaponBlockCollisionComponent* blockCollision = new WeaponBlockCollisionComponent(0);
		ent->addComponent((GameComponent*) blockCollision);
		ent->initializeComponents();

	} else if (name == "terrain") {
		ent->addComponent((GameComponent*) new TerrainOgreComponent(0));
		OgreBulletCollisions::CollisionShape *Shape;
		Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)

		/* CONSIDER weirnc-comment: Should the below be put in some type of "TerrainPhysicsComponent" class? 
		 * This seems like a weird place to put it.*/

		// a body is needed for the shape
		OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody("BasePlane",
				PhysicsManager::getInstance()->getWorld());
		PhysicsComponent* physicsComp = new PhysicsComponent(0);
		ent->addComponent(physicsComp);
		physicsComp->addCollisionShape(Shape);
		physicsComp->addRigidBody(defaultPlaneBody);
		defaultPlaneBody->setStaticShape(Shape, +0.1, 0.8);// (shape, restitution, friction)
		ent->initializeComponents();

	} else if (name == "firework") {
		ent->addComponent((GameComponent*) new WeaponOgreComponent(0));
		WeaponPhysicsComponent* weaponPhysics = new WeaponPhysicsComponent(0);
		//weaponPhysics->createMissile(
		//ent->addComponent((GameComponent*) new WeaponPhysicsComponent);
		ent->initializeComponents();

		Ogre::Vector3 vec(0, 10, 0);
		((OgreComponent*)ent->getComponent(COMPONENT_OGRE))->setInitialPosition(vec);
	}

	return ent;
}


