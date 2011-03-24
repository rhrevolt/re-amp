#ifndef __GameComponent_h__
#define __GameComponent_h__

typedef enum {
	COMPONENT_BROADCAST,
	COMPONENT_PHYSICS
} ComponentType;

class GameComponent
{
	public:
		GameComponent(int componentID, int priority = 0);
		~GameComponent(void);
		bool recieveMessage(int message);
		int getPriority(void);

		virtual bool tick(void) = 0;

		ComponentType type;
		
	private:
		int componentID;
		int priority; //TODO: Remove?
};

#endif // __GameComponent_h__
