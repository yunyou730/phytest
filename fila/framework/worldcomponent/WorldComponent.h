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
    static const char* ClsName() { return "WCGlobalRenderParam"; }
    LaunchParam launchParam;
    bool bLaunchParamDirty = false;
};

class WCKeyboardInput : public WorldComponent
{
public:
    static const char* ClsName() { return "WCKeyboardInput"; }
    WCKeyboardInput();
    
    void SetState(EInputKey key,EKeyState state);
    EKeyState GetState(EInputKey key) const;
    
    bool IsKeyPressed(EInputKey key) const { return GetState(key) == EKeyState::PRESS;}
    
    std::map<EInputKey,EKeyState>   _keyStateMap;
};


}
