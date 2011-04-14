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

#ifndef __Application_h_
#define __Application_h_

#include <boost/signals.hpp>

#include "core/BaseApplication.h"
#include "core/StateManager.h"

class Application : public Singleton<Application>, public BaseApplication
{
friend class Singleton<BaseApplication>;
public:
	Application(void);
	virtual ~Application(void);

	Ogre::Root* getRoot(){return mRoot;};
    Ogre::RenderWindow* getWindow(){return mWindow;};

	virtual void shutdownGame();

	// BOOST Signals
	/*
	 * signal_exiting - fired when the game is exiting.
	 * - no parameters
	 */
	boost::signal<void ()> signal_exiting;

	/*
	 * signal_exitgame - signal called when the game should exit.
	 * CAVEAT: If you're wanting the status of when the game exits
	 * listen to signal_exiting instead of this!
	 * - no parameter
	 */
	boost::signal<void ()> signal_exitgame;


protected:
	virtual void createScene(void);

	// Ogre::FrameListener
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt);

	StateManager* stateMgr;
};


#endif // #ifndef __Application_h_
