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
#include <stdlib.h>

#include "core/StateManager.h"

StateManager* StateManager::m_pInstance = NULL;
int StateManager::currentEntityID = 0;
int StateManager::currentStateID = -1;

StateManager* StateManager::instance()
{
	if(!m_pInstance)
		m_pInstance = new StateManager;

	return m_pInstance;
}

StateManager::~StateManager() 
{
	free(mmState);
	free(inGameState);
}

void StateManager::switchState(int stateID)
{
	GameState* oldState = currentState;
	// Switch the state
	switch (stateID) {
		case MAINMENUSTATE_ID:
			currentState = mmState;
			break;
		case INGAMESTATE_ID:
			currentState = inGameState;
			break;
		default:
			return;
	}
	// Notify the old state that it is inactive and the new state that it is active
	oldState->deactivate();
	currentState->activate();
	// Fire an event notifying of the state change
	StateChangeEvent evt;
	evt.oldState = currentStateID;
	evt.newState = stateID;
	EventManager::instance()->pushEvent(evt);
	// Change the current state ID
	currentStateID = stateID;
}

void StateManager::tick()
{
	currentState->tick();
}

int StateManager::getEntityID () 
{
	return currentEntityID++;
}

void StateManager::newGame()
{
	inGameState = new InGameState();
	mmState = new MainMenuState();
	currentState = inGameState;
}

