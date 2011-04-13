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

#include "core/GameEntity.h"
#include "boost/foreach.hpp"
#include "core/GameComponent.h"
#include <cstdlib>

GameEntity::GameEntity(int entityID, std::list<GameComponent*> comps) : entityID(entityID)
{
	// Empty
}

GameEntity::~GameEntity(void)
{
	//Free all of our components
	BOOST_FOREACH(GameComponent* comp, componentList)
	{
		free(comp);
	}
}

bool GameEntity::addComponent(GameComponent* component)
{
	// Add the component
	component->setParentEntity(this);
	componentList.push_back(component);
	return true;
}

bool GameEntity::removeComponent(GameComponent* component)
{
	// Try to remove the component
	componentList.remove(component);
	return true;
}

void GameEntity::initializeComponents()
{
	BOOST_FOREACH(GameComponent* comp, componentList)
	{
		comp->init();
	}
}

bool GameEntity::tick(FrameData &fd) {
	BOOST_FOREACH(GameComponent* comp, componentList)
	{
		comp->tick(fd);
	}

	return true;
}

bool GameEntity::receiveMessage(ComponentType comp, int message)
{
	return true;
}

GameComponent* GameEntity::getComponent(ComponentType type) 
{
	BOOST_FOREACH(GameComponent* comp, componentList)
	{
		if ((comp->getType()) == type) {
			return comp; 
		}
	}
}
