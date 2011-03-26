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

#include "core/InputManager.h"

#define KEYBOARD_INCREMENT 0.1f // How much to increment acceleration vector per cycle.
#define BUFFER_TIME_INTERVAL 0.1f // in seconds

InputManager::InputManager (std::string windowHandle) : 
	running(true),
	bufferedTicks(0),
	KEY_DOWN_DOWN(false),
	KEY_UP_DOWN(false),
	KEY_LEFT_DOWN(false),
	KEY_RIGHT_DOWN(false),
	currentFrameDelay(0.01f)
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

void InputManager::tick(const Ogre::FrameEvent& evt) {
	// Increment the number of ticks we've incremented
	bufferedTicks++;

	if (KEY_UP_DOWN)
		bufferedVector.x += KEYBOARD_INCREMENT;
	if (KEY_DOWN_DOWN)
		bufferedVector.x -= KEYBOARD_INCREMENT;
	if (KEY_RIGHT_DOWN)
		bufferedVector.y += KEYBOARD_INCREMENT;
	if (KEY_LEFT_DOWN)
		bufferedVector.y -= KEYBOARD_INCREMENT;

	
	// Check if we've buffered enough. 
	if (bufferedTicks >= (BUFFER_TIME_INTERVAL / currentFrameDelay)) {;
		// TODO: Create a new buffer event
		
		// Dump to console
		printf("Buffered Vector: (%f, %f)\n", bufferedVector.x, 
		       bufferedVector.y);

		// Reset the vector
		bufferedVector.x = 0;
		bufferedVector.y = 0;
		// Reset the tick count
		bufferedTicks = 0;
		
		// Update the timing information..
		// Check that the timeSinceLastEvent is not zero (for zero-div
		// reasons)
		if (evt.timeSinceLastEvent > 0) 
			currentFrameDelay = evt.timeSinceLastFrame;
		printf("New max tick count: %f\n", 
		       (BUFFER_TIME_INTERVAL / currentFrameDelay));
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
		KEY_UP_DOWN = true;
	}

	if (arg.key == OIS::KC_DOWN) {
		KEY_DOWN_DOWN = true;
	}

	if (arg.key == OIS::KC_RIGHT) {
		KEY_RIGHT_DOWN = true;
	}

	if (arg.key == OIS::KC_LEFT) {
		KEY_LEFT_DOWN = true;
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
	if (arg.key == OIS::KC_UP) {
		KEY_UP_DOWN = false;
	}

	if (arg.key == OIS::KC_DOWN) {
		KEY_DOWN_DOWN = false;
	}

	if (arg.key == OIS::KC_LEFT) {
		KEY_LEFT_DOWN = false;
	}

	if (arg.key == OIS::KC_RIGHT) {
		KEY_RIGHT_DOWN = false;
	}
	
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
