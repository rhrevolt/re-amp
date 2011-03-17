#ifndef __GameComponent_h__
#define __GameComponent_h__

class GameComponent
{
	public:
		GameComponent(int componentID);
		virtual ~GameComponent(void);
		virtual bool update(void);
	private:
		int componentID;
}

#endif // __GameComponent_h__
