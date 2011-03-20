/**
 * Re-Amp Project
 * Game Entity Model
 * (C) 2011 Re-Amp Contributors 
 */
 
#include "GameEntity.h"

bool compareByPriority(GameComponent* first, GameComponent* second) 
{
	return first->getPriority() > second->getPriority();
}

GameEntity::GameEntity(int entityID, std::list<GameComponent*> comps) : entityID(entityID) 
{
	// Empty
}

GameEntity::~GameEntity(void) 
{
	// Empty for now..
}

bool GameEntity::addComponent(GameComponent* component)
{
	// Add the component
	componentList.push_front(component);

	// Resort the list by priority
	componentList.sort(compareByPriority);
	
	// TODO: Add message bus firing here before returning.
	return true;
}

bool GameEntity::removeComponent(GameComponent* component)
{
	// Try to remove the component
	componentList.remove(component);
	if (true) {
		// TODO: Add message bus firing
		return true;
	}
	
	return false;
}



bool GameEntity::tick(void) {
	// Iterate over the component list
	std::list<GameComponent*>::iterator it = componentList.begin();
	std::list<GameComponent*>::iterator end = componentList.end();
	for (; it != end; it++) {
		(*it)->update();
	}
}

bool GameEntity::receiveMessage(ComponentType comp, int message)
{
	
}