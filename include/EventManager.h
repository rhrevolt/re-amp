#ifndef __EventManager_h__
#define __EventManager_h__

#include <boost/circular_buffer.hpp>

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
		bool pullEvent(int entityID);
		bool registerEntity(int entityID, EventType eventType);
	private:
		static EventManager* m_instance;
		boost::circular_buffer<EVENT> events;
		
};

#endif // __EventManager_h__

