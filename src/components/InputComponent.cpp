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

#include <stdio.h>
#include "components/InputComponent.h"
#include "core/InputManager.h"

InputComponent::InputComponent(int ID): GameComponent(ID)
{
	iManager = InputManager::getInstance();
	iManager->registerComponent(this);
	// Register with the event manager
	EventTypeList evts;
	evts.push_back(EVENT_ACCELERATION);
	evts.push_back(EVENT_KEYDOWN);
	evts.push_back(EVENT_KEYUP);
	EventManager::instance()->registerEntity(componentID, evts);
}

InputComponent::~InputComponent() {
	InputManager* iManager = InputManager::getInstance();
	//iManager->unregisterComponent(this);
};

bool InputComponent::tick(FrameData &fd)
{
	// Poll the event manager for vectors
	std::list<Event> evts = EventManager::instance()->pullEvent(componentID);
	BOOST_FOREACH(Event evt, evts) 
	{
		if (evt.eventType == EVENT_ACCELERATION) {
			InputEvent* iEvt = static_cast<InputEvent*>(&evt);
		}
	}
}
