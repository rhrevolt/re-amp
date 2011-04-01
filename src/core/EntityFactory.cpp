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

#include "components/OgreComponent.h"
#include "components/InputComponent.h"
#include "components/CarOgreComponent.h"
#include "components/CarPhysicsComponent.h"
#include "components/TerrainOgreComponent.h"

GameEntity* EntityFactory::create(std::string name)
{
	GameEntity* ent = new(GameEntity);

	// TODO: Perhaps this should be generated from a file?
	if (name == ("example")) {
		ent->addComponent((GameComponent*) new OgreComponent(0));
	} else if (name == "playerCar") {
		ent->addComponent((GameComponent*) new CarPhysicsComponent(0));
		ent->addComponent((GameComponent*) new CarOgreComponent(0));
		ent->addComponent((GameComponent*) new InputComponent(0));
	} else if (name == "terrain") {
		ent->addComponent((GameComponent*) new TerrainOgreComponent(0));
	}
	
	return ent;
}


