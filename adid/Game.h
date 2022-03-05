#pragma once
#include "application.h"

namespace fl
{
class Window;
}

namespace ad {

class Game : public fl::Application
{
public:
    Game();
    virtual ~Game();
    
    virtual void OnPrepare(const fl::LaunchParam& launchParam);
    virtual void OnCleanup();
    
    virtual void OnUpdate();
    virtual void OnRenderer();
    
    
protected:
    void CreateCamera(int viewportWidth,int viewportHeight);
    void CreateTest1();
    
};

}

