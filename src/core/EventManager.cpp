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
#include "core/EventManager.h"

EventManager* EventManager::m_instance = NULL;

EventManager* EventManager::instance() 
{
	if (!m_instance) 
		m_instance = new EventManager;
	
	return m_instance;
}

EventManager::EventManager()
{
}

EventManager::~EventManager(void)
{
}

bool EventManager::pushEvent(EVENT event)
{
	// adds the event to the back of the circular buffer
	events.push_back(event);
	return true;
}

EVENT EventManager::pullEvent(int entityID)
{
	// return a pointer to an event in the buffer	
	//BOOST_FOREACH(EVENT event, events)
	//{
	//	BOOST_FOREACH(pair<int, EventType>(entityID, eventTypes) pair,
	//			  registeredEntities)
	//	{
	//		if (pair.first == entityID)
	//		{
	//			BOOST_FOREACH(EventType eventType, pair.second)
	//			{
	//				if (eventType == event.eventType)
	//				{
	//					// Pass reference to message to appropriate component
	//				} 
	//			}
	//		}
	//	}
	
}	

bool EventManager::registerEntity(int entityID,
		std::list<EventType eventTypes)
{
	// register a component for a specific event type
	registeredEntities.insert(pair<int, EventType>(entityID, eventTypes));	
	return true;
}
