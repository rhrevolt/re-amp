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

#include "components/InputComponent.h"
#include "components/CarOgreComponent.h"
#include "components/CarPhysicsComponent.h"
#include "components/TerrainOgreComponent.h"
#include "components/PhysicsComponent.h"
#include "components/CameraComponent.h"
#include "components/CarSoundComponent.h"

#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h"


GameEntity* EntityFactory::create(std::string name)
{
	GameEntity* ent = new(GameEntity);

	// TODO: Perhaps this should be generated from a file?
	if (name == "playerCar") {
		
		CarOgreComponent* carOgre = new CarOgreComponent(0);
		carOgre->init();
		ent->addComponent((GameComponent*) carOgre);
		CarPhysicsComponent* carPhysics = new CarPhysicsComponent(0);
		ent->addComponent((GameComponent*) carPhysics);
		carPhysics->init();

		ent->addComponent((GameComponent*) new CameraComponent(0));
		ent->addComponent((GameComponent*) new CarSoundComponent(0));

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
		defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8);// (shape, restitution, friction)


	}

	return ent;
}


