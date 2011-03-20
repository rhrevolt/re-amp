#ifndef __GameEntity_h__
#define __GameEntity_h__

#include <list> 
#include "GameComponent.h"

bool compareComponents(GameComponent* first, GameComponent* second);

typedef enum {
	COMPONENT_BROADCAST,
	COMPONENT_PHYSICS
} ComponentType;

class GameEntity
{
	public:
		GameEntity(int entityID = 0, std::list<GameComponent*> comps = 
		           (std::list<GameComponent*>)NULL);
		~GameEntity(void);
		
		bool tick(void);
		bool receiveMessage(ComponentType comp, int message);
		
		bool addComponent(GameComponent* component);
		bool removeComponent(GameComponent* component);
		bool removeComponent(int componentID); 
		
	private:
		int entityID;
		std::list<GameComponent*> componentList;
};

#endif // __GameEntity_h__
