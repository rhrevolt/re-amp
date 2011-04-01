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

#include "config.h"
#include "core/Application.h"
#include "core/StateManager.h"

//-------------------------------------------------------------------------------------
Application::Application(void)
{
	stateMgr = StateManager::getInstance();
}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{
	free(stateMgr);
}

//-------------------------------------------------------------------------------------
void Application::createScene(void)
{
	//Start our sample game
	
	//weirnc: Is this really the right place to put this?
	stateMgr->newGame();
}

bool Application::frameStarted(const Ogre::FrameEvent& evt)
{
	// Construct a FrameData event
	FrameData& fd = (FrameData&)evt;
	fd.frameType = FRAME_PRERENDER;
	// Tick the state manager
	stateMgr->tick(fd);

	return true;
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	// Check if the window is closed
	if (mWindow->isClosed()) {
		return false;
	}

	// Make sure that we aren't shutting down
	// TODO: Instead of polling the inputmanager for status, have it listen
	// for the event
	if (!mInputManager->getStatus()) {
		return false;
	}

	// TODO: fire events to the statemanager
	return true;
}

bool Application::frameEnded(const Ogre::FrameEvent& evt) 
{
	// TODO: fire events to the statemanager
	return true;
}
