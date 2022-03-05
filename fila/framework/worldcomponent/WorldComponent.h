#pragma once
#include "window.h"
#include <map>

namespace fl {

class WorldComponent
{
public:
    virtual ~WorldComponent() {}
};

class WCGlobalRenderParam : public WorldComponent
{
public:
    LaunchParam launchParam;
};

class WCKeyboardInput : public WorldComponent
{
public:
    WCKeyboardInput();
    
    void SetState(EInputKey key,EKeyState state);
    EKeyState GetState(EInputKey key) const;
    
    std::map<EInputKey,EKeyState>   _keyStateMap;
};

}
