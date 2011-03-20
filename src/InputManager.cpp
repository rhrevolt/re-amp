/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * re-amp
 * Copyright (C)  2011 <>
 * 
 * re-amp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * re-amp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "InputManager.h"

InputManager::InputManager (void)
{
	// Initialize the input manager and the keyboard/mouse
	oisInputManager = OIS::InputManager::createInputSystem (parameterList);
	mKeyboard = static_cast<OIS::Keyboard*>(oisInputManager->createInputObject (OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(oisInputManager->createInputObject (OIS::OISMouse, true));
	// Add ourselves as an event listener
	mKeyboard->setEventCallback (this);
	mMouse->setEventCallback (this);
}

InputManager::~InputManager (void)
{
	// Shutdown OIS
	oisInputManager->destroyInputObject (mKeyboard);
	oisInputManager->destroyInputObject (mMouse);
	OIS::InputManager::destroyInputSystem (oisInputManager);
	oisInputManager = 0;
}

bool InputManager::keyPressed (const OIS::KeyEvent &arg) {
	// Got a keypress event
	printf("Got keypress event: %d\n", arg.key);
	return true;
	
}

bool InputManager::keyReleased (const OIS::KeyEvent &arg) {
	// Got a keyrelease event
	printf("Got keyrelease event: %d\n", arg.key);
	return true;

}

bool InputManager::mouseMoved (const OIS::MouseEvent &arg) {
	// Got a mouse movement event
	printf("Got mousemoved event\n");
	return true;

}

bool InputManager::mousePressed (const OIS::MouseEvent &arg) {
	// Got a mouse press event
	printf("Got mouse press event\n");
	return true;

}

bool InputManager::mouseReleased (const OIS::MouseEvent &arg) {
	// Got a mouse movement event
	printf("Got mouse released event");
	return true;
}
