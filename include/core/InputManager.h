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

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include <cstdlib>
#include <stdio.h>

// OIS Includes
#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

// Windows Headers
#if defined OIS_WIN32_PLATFORM
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#ifdef min
#undef min
#endif
LRESULT DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
// Linux Headers
#elif defined OIS_LINUX_PLATFORM
#include <X11/Xlib.h>
#include <X11/Xatom.h>
void checkX11Events();
#endif

// Ogre includes
#include <OgrePrerequisites.h>
#include <OgreFrameListener.h>
#include <OgreVector2.h>

// Our includes
#include "core/EventManager.h"
#include "core/StateManager.h"
#include "core/SubSystemManager.h"
#include "core/Singleton.h"
//#include "components/CarPhysicsComponent.h"

class InputManager: public SubSystemManager, public OIS::KeyListener, public OIS::MouseListener, public Singleton<InputManager>
{
friend class Singleton<InputManager>;
public:
	void init(std::string windowHandle);
	bool tick(FrameData&);
	bool registerComponent(GameComponent*);

	void updateClippingArea(unsigned int height, unsigned int width);
	void shutdownManager (void);
	void capture (void);
	bool getStatus(void);

	bool keyPressed (const OIS::KeyEvent &arg);
	bool keyReleased (const OIS::KeyEvent &arg);
	bool mouseMoved (const OIS::MouseEvent &arg);
	bool mousePressed (const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool mouseReleased (const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	bool KEY_LEFT;
	bool KEY_RIGHT;
	bool KEY_ACCEL;
	bool KEY_BRAKE;
	bool KEY_HORN;
	bool KEY_FIRE;
	bool KEY_RESET;

protected:
	;

private:
	InputManager ();
	~InputManager (void);

	OIS::InputManager* oisInputManager;
	OIS::Keyboard* mKeyboard;
	OIS::Mouse* mMouse;

	bool running;

};

#endif // _INPUT_MANAGER_H_
