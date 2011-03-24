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

#include "core/InputManager.h"


InputManager::InputManager (std::string windowHandle) : running(true)
{
	OIS::ParamList parameterList;
	// Insert the Window ID
	parameterList.insert(std::make_pair(std::string("WINDOW"), windowHandle));
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
	shutdownManager ();
	free(oisInputManager);
	free(mKeyboard);
	free(mMouse);
}

void InputManager::shutdownManager(void)
{
	if (oisInputManager) {
		// Shutdown OIS
		oisInputManager->destroyInputObject (mKeyboard);
		oisInputManager->destroyInputObject (mMouse);
		OIS::InputManager::destroyInputSystem (oisInputManager);
		oisInputManager = 0;
	}
}

void InputManager::capture(void)
{
	mKeyboard->capture();
	mMouse->capture();
}

bool InputManager::getStatus(void)
{
	if (!running)
		printf("stopping..");
	return running;
}

void InputManager::updateClippingArea (unsigned int width, unsigned int height)
{
	if (mMouse) {
		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width = width;
		mouseState.height = height;
	}
}

bool InputManager::keyPressed (const OIS::KeyEvent &arg) {
	// Got a keypress event
	// Check for escape -- it's hard-wired as a quit
	if (arg.key == OIS::KC_ESCAPE) {
		EVENT evt;
		evt.eventType = EVENT_SHUTDOWN;
		EventManager::instance()->pushEvent(evt);
		running = false;
	}

	if (arg.key == OIS::KC_UP) {
        EVENT evt;
        evt.eventType = EVENT_ACCELERATE;
        EventManager::instance()->pushEvent(evt);
	}

	if (arg.key == OIS::KC_DOWN) {
        EVENT evt;
        evt.eventType = EVENT_DECELERATE;
        EventManager::instance()->pushEvent(evt);
	}

	if (arg.key == OIS::KC_RIGHT) {
        EVENT evt;
        evt.eventType = EVENT_RIGHT_TURN;
        EventManager::instance()->pushEvent(evt);
	}

	if (arg.key == OIS::KC_LEFT) {
        EVENT evt;
        evt.eventType = EVENT_LEFT_TURN;
        EventManager::instance()->pushEvent(evt);
	}

	if (arg.key == OIS::KC_H) {
        EVENT evt;
        evt.eventType = EVENT_HORN;
        EventManager::instance()->pushEvent(evt);
	}

	if (arg.key == OIS::KC_SPACE){
        EVENT evt;
        evt.eventType = EVENT_FIRE;
        EventManager::instance()->pushEvent(evt);
	}

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

bool InputManager::mousePressed (const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	// Got a mouse press event
	printf("Got mouse press event\n");
	return true;

}

bool InputManager::mouseReleased (const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	// Got a mouse movement event
	printf("Got mouse released event");
	return true;
}
