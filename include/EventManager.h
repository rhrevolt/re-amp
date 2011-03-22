#ifndef __EventManager_h__
#define __EventManager_h__

#include <boost/circular_buffer.hpp>

typedef enum {
	EVENT_DAMAGE,
	EVENT_ACCELERATE
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
		bool pullEvent();
		bool registerComp(int entityID, EventType eventType);
	private:
		boost::circular_buffer<EVENT> events;
		
};

#endif // __EventManager_h__

