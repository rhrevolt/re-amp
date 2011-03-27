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

#ifndef __GameComponent_h__
#define __GameComponent_h__

#include "core/FrameData.h"

typedef enum {
	COMPONENT_BROADCAST,
	COMPONENT_PHYSICS
} ComponentType;

class GameEntity; // forward declaration

class GameComponent
{
	public:
		GameComponent(int componentID, int priority = 0);
		~GameComponent(void);
		bool recieveMessage(int message);
		int getPriority(void);
		bool setParentEntity(GameEntity* parent);

		virtual bool tick(FrameData &fd) = 0;

		ComponentType type;
		
	protected:
		GameEntity* parentEntity;
		
	private:
		int componentID;
		int priority; //TODO: Remove?
		
		
};

#endif // __GameComponent_h__
