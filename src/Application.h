#ifndef __Application_h_
#define __Application_h_

#include "BaseApplication.h"

class Application : public BaseApplication
{
public:
    Application(void);
    virtual ~Application(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __Application_h_
