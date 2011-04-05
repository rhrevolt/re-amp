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

#include <Ogre.h>
#include "states/InGameState.h"
#include "core/GameComponent.h"
#include "components/TerrainOgreComponent.h"


/*
   GameSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
   GameSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

   Ogre::Light* pointLight = GameSceneMgr->createLight("pointLight");
   pointLight->setType(Ogre::Light::LT_POINT);
   pointLight->setPosition(Ogre::Vector3(100, 150, 250));

   Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

   Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
   plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

   Ogre::Entity* entGround = GameSceneMgr->createEntity("GroundEntity", "ground");
   GameSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

   entGround->setCastShadows(false);
   */


void TerrainOgreComponent::init()
{
	Ogre::SceneManager* sMgr = StateManager::getInstance()->inGameState->getSceneMgr();

	// Copy-pasted from the tutorials, need to tweak
	sMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	sMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 15000, 15000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround =sMgr->createEntity("GroundEntity", "ground");
	sMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

	entGround->setCastShadows(false);

	Ogre::Light* pointLight = sMgr->createLight("pointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(Ogre::Vector3(0, 150, 250));

	pointLight->setDiffuseColour(1.0, 0.0, 0.0);
	pointLight->setSpecularColour(1.0, 0.0, 0.0);
}
