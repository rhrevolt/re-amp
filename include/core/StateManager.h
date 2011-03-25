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

#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include "core/GameEntity.h"
#include "core/GameState.h"
#include "core/EventManager.h"
#include "states/InGameState.h"
#include "states/MainMenuState.h"

/**
 An event for when the state changes
 */
struct StateChangeEvent : public EVENT {
	int oldState;
	int newState;
};

//StateManager is a singleton!
class StateManager
{
public:
	static StateManager* instance();

	const static int menuID;
	const static int inGameID;
	const static int exitGameID;

	void tick();
	void newGame();

	void switchState(int stateID);

	int getEntityID();
	
	GameState* currentState;

protected:
	MainMenuState*  mmState;
	InGameState*	inGameState; 
	static int		currentEntityID;
	static int		currentStateID;
	
private:
	StateManager(){};
	~StateManager();

	static StateManager* m_pInstance;
};

#endif // _STATE_MANAGER_H_
