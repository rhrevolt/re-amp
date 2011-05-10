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

#include <boost/signals.hpp>

#include "core/FrameData.h"

typedef enum {
	COMPONENT_BROADCAST,
	COMPONENT_PHYSICS,
	COMPONENT_OGRE,
	COMPONENT_INPUT,
	COMPONENT_SOUND,
	COMPONENT_TERRAINOGRE,
	COMPONENT_WEAPON,
	COMPONENT_CAMERA,
	COMPONENT_HUD,
} ComponentType;

class GameEntity; // forward declaration

class GameComponent : public boost::signals::trackable
{
	public:
		GameComponent(int componentID);
		~GameComponent(void);
		bool setParentEntity(GameEntity* parent);

		virtual bool tick(FrameData &fd) = 0;

		virtual ComponentType getType() = 0;

		virtual void init() = 0;

	protected:
		GameEntity* parentEntity;
		int componentID;

	private:

};

#endif // __GameComponent_h__
