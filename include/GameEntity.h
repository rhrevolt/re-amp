#ifndef __GameEntity_h__
#define __GameEntity_h__

#include <list> 
#include "GameComponent.h"

bool compareComponents(GameComponent* first, GameComponent* second);

class GameEntity
{
	public:
		GameEntity(int entityID);
		virtual ~GameEntity(void);
		virtual bool update(void);
		bool addComponent(GameComponent* component);
		bool removeComponent(GameComponent* component);
		bool removeComponent(int componentID); 
	private:
		int entityID;
		std::list<GameComponent*> componentList;
};

#endif // __GameEntity_h__
