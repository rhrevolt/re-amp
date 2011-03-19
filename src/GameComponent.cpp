/**
 * Re-Amp Project
 * Game Entity Model
 * (C) 2011 Re-Amp Contributors 
 */

#include "GameComponent.h"

GameComponent::GameComponent(int componentID, int priority) : componentID(componentID), priority(priority)
{

}

GameComponent::~GameComponent(void) 
{
	
}

int GameComponent::getPriority(void)
{
	return priority;
}

