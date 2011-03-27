#ifndef __EventManager_h__
#define __EventManager_h__

#include <boost/circular_buffer.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <list>

using namespace std;

typedef enum {
	EVENT_DAMAGE,
	EVENT_ACCELERATE,
	EVENT_SHUTDOWN
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
		EVENT pullEvent(int entityID);
		bool registerEntity(int entityID, std::list<EventType> eventTypes);
	private:
		static EventManager* m_instance;
		// Circular buffer of events waiting to be pulled
		boost::circular_buffer<EVENT> events;
		// Multipmap to keep track of which Events are
		// associated with an entity
		std::multimap<int, std::list<EventType>> registeredEntities;
		
		
};

#endif // __EventManager_h__

