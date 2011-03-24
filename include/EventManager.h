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

