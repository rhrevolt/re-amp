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

#ifndef __EventManager_h__
#define __EventManager_h__

#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>
#include <map>

using namespace std;

typedef enum {
	EVENT_DAMAGE,
	EVENT_ACCELERATE,
	EVENT_SHUTDOWN,
	EVENT_DECELERATE,
	EVENT_LEFT_TURN,
	EVENT_HORN,
	EVENT_RIGHT_TURN,
	EVENT_FIRE
} EventType;

struct EVENT {
	int eventID;
	EventType eventType;
	char* description;
};

// Singleton
class EventManager
{
	public:
		static EventManager* instance();

		EventManager();
		~EventManager(void);
		bool pushEvent(EVENT event);
		bool pullEvent(int entityID);
		bool registerEntity(int entityID, EventType eventType);
	private:
		static EventManager* m_instance;
		// Circular buffer of events waiting to be pulled
		boost::circular_buffer<EVENT> events;
		// Multipmap to keep track of which Events are
		// associated with an entity
		std::multimap<int, EventType> registeredEntities;

};

#endif // __EventManager_h__

