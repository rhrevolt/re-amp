/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ReAmp
 * Copyright (C)  2011 <>
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

#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include "GameEntity.h"
#include "GameState.h"
#include "InGameState.h"
#include "MainMenuState.h"
#include "ExitGameState.h"

//StateManager is a singleton!
class StateManager
{
public:
	static StateManager* instance();
	
	void tick();
	void newGame();

	int getEntityID();
	
	GameState* currentState;

protected:
	MainMenuState*  mmState;
	InGameState*	inGameState; 
	ExitGameState*	exitGameState;
	static int		currentEntityID;
	
private:
	StateManager(){};
	~StateManager();

	static StateManager* m_pInstance;
};

#endif // _STATE_MANAGER_H_
