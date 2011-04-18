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
#include "core/FrameData.h"
#include "core/Singleton.h"

//StateManager is a singleton!
class StateManager: public Singleton<StateManager>
{
	friend class Singleton<StateManager>;
	public:
	static GameState* getCurrentState();

	const static int menuID;
	const static int inGameID;
	const static int exitGameID;

	void tick(FrameData &fd);
	void newGame();

	void switchState(int stateID);

	int getEntityID();

	GameState* currentState;
	GameState*  mmState;
	GameState*	inGameState; 

	// BOOST signals
	boost::signals<void (int oldState, int newState)> signal_stateChanged;

	protected:
	static int		currentEntityID;
	static int		currentStateID;

	private:
	StateManager();
	~StateManager();
};

#endif // _STATE_MANAGER_H_
