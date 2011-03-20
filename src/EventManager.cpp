#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager(void)
{
}

bool EventManager::pushEvent(EVENT event)
{
	events.push_back(event);
	return true;
}

bool EventManager::pullEvent()
{

}	

bool EventManager::registerComp(int entityID, EventType eventType)
{
	
}
