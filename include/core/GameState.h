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

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "core/GameEntity.h"
#include <Ogre.h>
#include "core/FrameData.h"

class GameState
{
public:
	virtual int returnStateID() = 0;
	virtual void tick(FrameData &fd) = 0;
	
	virtual void activate(){};
	virtual void deactivate(){};

	virtual void start() = 0;

	GameEntity* getEntity(int ID);

	virtual Ogre::SceneManager* getSceneMgr() = 0;

protected:
	std::list<GameEntity*> entityList;
	
private:
	

};

#endif // _GAMESTATE_H_
