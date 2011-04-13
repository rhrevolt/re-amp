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

#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include <boost/signals.hpp>

#include "core/GameComponent.h"
#include "core/InputManager.h"


class InputComponent: public GameComponent
{
	public:
		InputComponent(int ID);
		~InputComponent();
		virtual bool tick(FrameData &fd);
	
		virtual void init();

		virtual ComponentType getType() {return COMPONENT_INPUT;};

		// BOOST Signals
		/*
		 * signal_honk
		 * - start - boolean - whether the signal indicates the honk key is down
     */ 
		boost::signal<void (bool)> signal_honk;

		/*
		 * signal_weapon
		 * no parameters -- called once when the weapon button is pressed. no repeats.
		 */
		boost::signal<void ()> signal_weapon;

		/*
		 * signal_acceleration
		 * - bufferedVector - Ogre::Vector2 - vector to indicate acceleration 
		 *   contained in the event.
		 */
		boost::signal<void (Ogre::Vector2)> signal_acceleration;
	
	private:
		InputManager* iManager;
};

#endif // _INPUTCOMPONENT_H_
