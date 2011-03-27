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
#include <cstdlib>

bool compareByPriority(GameComponent* first, GameComponent* second)
{
	return first->getPriority() > second->getPriority();
}

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
	componentList.push_front(component);

	// Resort the list by priority
	componentList.sort(compareByPriority);

	// TODO: Add message bus firing here before returning.
	return true;
}

bool GameEntity::removeComponent(GameComponent* component)
{
	// Try to remove the component
	componentList.remove(component);
	if (true) {
		// TODO: Add message bus firing
		return true;
	}

	return false;
}



bool GameEntity::tick(void) {
	BOOST_FOREACH(GameComponent* comp, componentList)
	{
		comp->tick();
	}
}

bool GameEntity::receiveMessage(ComponentType comp, int message)
{

}
