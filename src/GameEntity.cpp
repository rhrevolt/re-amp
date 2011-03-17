/**
 * Re-Amp Project
 * Game Entity Model
 * (C) 2011 Re-Amp Contributors 
 */
 
#include "GameEntity.h"

bool compareComponents(GameComponent* first, GameComponent* second) 
{
	return first->getPriority() > second->getPriority();
}

GameEntity::GameEntity(int entityID) : entityID(entityID) 
{
	// Empty
}

GameEntity::~GameEntity(void) 
{
	// Empty for now..
}

bool GameEntity::update(void) {
	// Iterate over the component list
	for (std::list<GameComponent*>::iterator it = componentList.begin(); it != componentList.end(); it++) {
		(*it)->update();
	}
}

bool GameEntity::addComponent(GameComponent* component)
{
	// Add the component
	componentList.push_front(component);

	// Resort the list
	componentList.sort(compareComponents);
	
	// Return success
	return true;
}
