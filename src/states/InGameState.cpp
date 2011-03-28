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

#include "boost/foreach.hpp"

#include "core/GameEntity.h"
#include "core/EntityFactory.h"
#include "states/InGameState.h"

InGameState::InGameState()
{
	physicsManager = new PhysicsManager();
	
	entityList.push_back(EntityFactory::create("playerCar"));
}	

InGameState::~InGameState()
{
	free(physicsManager);
	
	BOOST_FOREACH(GameEntity* ent, entityList) {
		free(ent);
	}
}

void InGameState::tick(FrameData &fd)
{
	physicsManager->tick(fd);
	
	BOOST_FOREACH(GameEntity* ent, entityList) {
		ent->tick(fd);
	}
}

int InGameState::returnStateID()
{
	return INGAMESTATE_ID;
}


