#pragma once
#include "application.h"

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
};

}

