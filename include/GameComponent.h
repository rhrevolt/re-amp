#ifndef __GameComponent_h__
#define __GameComponent_h__

class GameComponent
{
	public:
		GameComponent(int componentID, int priority);
		virtual ~GameComponent(void);
		virtual bool update(void);
		int getPriority(void);
	private:
		int componentID;
		int priority;
};

#endif // __GameComponent_h__
