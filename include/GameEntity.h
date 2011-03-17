#ifndef __GameEntity_h__
#define __GameEntity_h__

class GameEntity
{
	public:
		GameEntity(int entityID);
		virtual ~GameEntity(void);
		virtual bool update(void);
		void addComponent(GameComponent* component);
		void removeComponent(GameComponent* component);
		void removeComponent(int componentID); 
	private:
		int entityID;
}

#endif // __GameEntity_h__
