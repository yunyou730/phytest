#pragma once
#include "window.h"
#include <map>
#include "box2d.h"

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

class WCPhy2DSettings : public WorldComponent
{
public:
    static const char* ClsName() { return "WCPhy2DSettings";}
        
    WCPhy2DSettings();
    
    /*
     物理与显示的比例
     比如 一个屏幕 在 orho 的 情况下，假设 上下显示范围是 [-1,1]
     上下能容纳 50 个物理单位
     则这个值是 (1 - (-1)) / 50 = 0.04
     **/
    float Ratio() const { return _ratio;}
    float _ratio = 0.04;
    
    // phy setting
    b2Vec2  _gravity;   // default (0.0f,-10.0f);
    int32   _velocityIterations = 6;
    int32   _positionIterations = 2;
    // iterate times in one second
    int     _phyFPS = 30;
    float   TimeStep() const;
};

class WCImGUISettings : public WorldComponent
{
public:
    static const char* ClsName() { return "WCImGUISettings";}
    
    bool    _bSizeChanged = false;
    int     _width = 0;
    int     _height = 0;
};


}
