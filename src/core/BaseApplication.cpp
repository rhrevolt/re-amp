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

/* NOTE: This file is originally derived from the OgreWiki */

#include "core/BaseApplication.h"

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
	: mRoot(0),
	mCamera(0),
	mSceneMgr(0),
	mWindow(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	mCursorWasVisible(false),
	mShutDown(false),
	mInputManager(0)
{
}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
	// Check if we have a config file. If so, load that..if not, show the config dialog.
	if (!mRoot->restoreConfig()) {
		if(mRoot->showConfigDialog())
		{
			// Save the config file
			mRoot->saveConfig();
			Ogre::LogManager::getSingletonPtr()->logMessage("*** Saved Configuration File");

		} else {
			// User clicked cancel, abort.
			Ogre::LogManager::getSingletonPtr()->logMessage("*** User cancelled configuration -- aborting");
			return false;
		}
	}

	// Here we choose to let the system create a default rendering window by passing 'true'
	mWindow = mRoot->initialise(true, "Re-Amp");
	return true;
}
void BaseApplication::shutdownGame(void)
{
	mShutDown = true;
}
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing Input Manager ***");

	// Get the window ID
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;

	mInputManager = InputManager::getInstance();
	mInputManager->init(windowHndStr.str());

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	// Add ourself (actually, Application) as a frame listener
	mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
		}
	}
}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{

	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";

	if (!setup()) {
		Ogre::LogManager::getSingletonPtr()->logMessage("*** setup() call failed -- aborting");
		return;
	}

	mRoot->startRendering();

}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	if (!configure()) {
		Ogre::LogManager::getSingletonPtr()->logMessage("*** configure() call failed -- aborting");
		return false;
	}

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();

	return true;
};

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	mInputManager->updateClippingArea(width, height);
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mWindow )
	{
		// Tell the input system to be destroyed
		mInputManager->shutdownManager ();
	}
}
