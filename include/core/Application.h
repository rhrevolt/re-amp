#ifndef __Application_h_
#define __Application_h_

#include "core/BaseApplication.h"
#include "core/StateManager.h"

class Application : public BaseApplication
{
public:
    Application(void);
    virtual ~Application(void);

protected:
    virtual void createScene(void);
    virtual void mainLoopPreRender(void); 
    virtual void mainLoopPostRender(void);

	StateManager* stateMgr;
};

#endif // #ifndef __Application_h_
