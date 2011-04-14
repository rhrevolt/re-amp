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
#include "components/InputComponent.h"
#include "core/Application.h"

#define KEYBOARD_INCREMENT 1.0f // How much to increment acceleration vector per cycle.
#define BUFFER_TIME_INTERVAL 0.05f // in seconds

InputManager::InputManager () :
	KEY_ACCEL(false),
	KEY_BRAKE(false),
	KEY_LEFT(false),
	KEY_RIGHT(false),
	currentFrameDelay(1.0f)
{
}

void InputManager::init(std::string windowHandle) {
	OIS::ParamList parameterList;
	// Insert the Window ID
	parameterList.insert(std::make_pair(std::string("WINDOW"), windowHandle));
	// Make the input manager nonexclusive
#if defined OIS_WIN32_PLATFORM
	parameterList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	parameterList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	parameterList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	parameterList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	parameterList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	parameterList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	parameterList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	parameterList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif
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
		mKeyboard = 0;
		mMouse = 0;
	}
}

void InputManager::capture(void)
{
	if (mKeyboard)
		mKeyboard->capture();
	if (mMouse)
		mMouse->capture();
}

void InputManager::updateClippingArea (unsigned int width, unsigned int height)
{
	if (mMouse) {
		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width = width;
		mouseState.height = height;
	}
}

bool InputManager::tick(FrameData& evt) {
	// Fire an acceleration signal if any of those keys were pressed
	if (KEY_ACCEL | KEY_BRAKE | KEY_RIGHT | KEY_LEFT)
	{
		Ogre::Vector2 inputVector(0, 0);

		if (mKeyboard->isKeyDown(OIS::KC_UP) || mKeyboard->isKeyDown(OIS::KC_W))
			inputVector.y += 1;
		if (mKeyboard->isKeyDown(OIS::KC_DOWN) || mKeyboard->isKeyDown(OIS::KC_S))
			inputVector.y -= 1;
		if (mKeyboard->isKeyDown(OIS::KC_LEFT) || mKeyboard->isKeyDown(OIS::KC_A))
			inputVector.x += 1;
		if (mKeyboard->isKeyDown(OIS::KC_RIGHT) || mKeyboard->isKeyDown(OIS::KC_D))
			inputVector.x -= 1;
		// Push the vector
		signal_acceleration(inputVector);
	}
}

bool InputManager::keyPressed (const OIS::KeyEvent &arg) {
	// Got a keypress event
	// Check for escape -- it's hard-wired as a quit

	if (arg.key == OIS::KC_ESCAPE) {
		Application::getInstance()->signal_exitgame();
	}

	if (arg.key == OIS::KC_UP || arg.key == OIS::KC_W) {
		KEY_ACCEL = true;
	}

	if (arg.key == OIS::KC_DOWN || arg.key == OIS::KC_S) {
		KEY_BRAKE = true;
	}

	if (arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_D) {
		KEY_RIGHT = true;
	}

	if (arg.key == OIS::KC_LEFT || arg.key == OIS::KC_A) {
		KEY_LEFT = true;
	}

	if (arg.key == OIS::KC_H) {
		signal_honk(true);
		KEY_HORN = true;
	}

	if (arg.key == OIS::KC_SPACE){
		signal_weapon();
		KEY_FIRE = true;
	}

	if (arg.key == OIS::KC_R) {
		signal_reset();
		KEY_RESET = true;
	}

	// Fire a generic signal
	signal_keydown(arg);

	return true;

}

bool InputManager::keyReleased (const OIS::KeyEvent &arg) {
	// Got a keyrelease event
	if (arg.key == OIS::KC_UP || arg.key == OIS::KC_W) {
		KEY_ACCEL = false;
	}

	if (arg.key == OIS::KC_DOWN || arg.key == OIS::KC_S) {
		KEY_BRAKE = false;
	}

	if (arg.key == OIS::KC_LEFT || arg.key == OIS::KC_A) {
		KEY_LEFT = false;
	}

	if (arg.key == OIS::KC_RIGHT || arg.key == OIS::KC_D) {
		KEY_RIGHT = false;
	}

	if (arg.key == OIS::KC_H) {
		signal_honk(false);
	}

	if (arg.key == OIS::KC_SPACE){
		KEY_FIRE = false;
	}

	if (arg.key == OIS::KC_R) {
		KEY_RESET = false;
	}
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
