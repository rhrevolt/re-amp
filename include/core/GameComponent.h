#ifndef __GameComponent_h__
#define __GameComponent_h__

typedef enum {
	COMPONENT_BROADCAST,
	COMPONENT_PHYSICS
} ComponentType;

class GameEntity; // forward declaration

class GameComponent
{
	public:
		GameComponent(int componentID, int priority = 0);
		~GameComponent(void);
		bool recieveMessage(int message);
		int getPriority(void);
		bool setParentEntity(GameEntity* parent);

		virtual bool tick(void) = 0;

		ComponentType type;
		
	protected:
		GameEntity* parentEntity;
		
	private:
		int componentID;
		int priority; //TODO: Remove?
		
		
};

#endif // __GameComponent_h__
