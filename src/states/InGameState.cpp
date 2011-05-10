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

#include <stdio.h>

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/GameEntity.h"
#include "core/EntityFactory.h"
#include "states/InGameState.h"
#include <OgreRoot.h>



InGameState::InGameState()
{
	// Initialize our SceneManager
	Ogre::Root* root = Ogre::Root::getSingletonPtr();
	GameSceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
	
	physicsManager = PhysicsManager::getInstance();
	inputManager = InputManager::getInstance();
	soundManager = SoundManager::getInstance();
}	

InGameState::~InGameState()
{
	free(physicsManager);
	
	BOOST_FOREACH(GameEntity* ent, entityList) {
		free(ent);
	}
}

void InGameState::start()
{
	physicsManager->init();
	// TODO: get map file name from somewhere else..
	loadFromXML("maps/map_01.xml");

	/*entityList.push_back(EntityFactory::create("terrain"));
	entityList.push_back(EntityFactory::create("playerCar"));
	entityList.push_back(EntityFactory::create("car"));
	entityList.push_back(EntityFactory::create("weapon block"));
	*/
	// CONSIDER: weirnc: Not sure where else to put this... seems like a good place? I'm stupid
	InputManager::getInstance()->signal_weapon.connect(boost::bind(&InGameState::pushNewEntityToList, this, "firework"));
} 

void InGameState::loadFromXML(const std::string &fileName)
{
	using boost::property_tree::ptree;
	ptree pTree;
	// Load the XML file
	read_xml(fileName, pTree);
	// TODO: Parse the tree into map entities
	BOOST_FOREACH(ptree::value_type &v, pTree.get_child("map")) {
		printf("got object\n");
	}
}

void InGameState::pushNewEntityToList(std::string entityName)
{
	entityList.push_back(EntityFactory::create(entityName));
}

void InGameState::tick(FrameData &fd)
{
	inputManager->capture();
	inputManager->tick(fd);
	physicsManager->tick(fd);
	soundManager->tick(fd);
	
	BOOST_FOREACH(GameEntity* ent, entityList) {
		ent->tick(fd);
	}
}

int InGameState::returnStateID()
{
	return INGAMESTATE_ID;
}

Ogre::SceneManager* InGameState::getSceneMgr()
{
	return GameSceneMgr;
}

