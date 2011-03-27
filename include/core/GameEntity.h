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

#ifndef __GameEntity_h__
#define __GameEntity_h__

#include <list> 
#include "core/GameComponent.h"
#include "core/FrameData.h"

bool compareComponents(GameComponent* first, GameComponent* second);

class GameEntity
{
	public:
		GameEntity(int entityID = 0, std::list<GameComponent*> comps = 
		           (std::list<GameComponent*>)NULL);
		~GameEntity(void);
		
		bool tick(FrameData &fd);
		bool receiveMessage(ComponentType comp, int message);
		
		bool addComponent(GameComponent* component);
		bool removeComponent(GameComponent* component);
		bool removeComponent(int componentID); 
		
	private:
		int entityID;
		std::list<GameComponent*> componentList;
};

#endif // __GameEntity_h__
