#pragma once

#define SAFE_DEL(pointer) {\
if(pointer != nullptr) \
{\
    delete pointer;\
    pointer = nullptr;\
}\
}\

#define CLASS_NAME(name) #name

#define DELCARE_SINGLETON(CLS_NAME) \
friend class Application;\
public:\
static CLS_NAME* Instance() \
{\
    static CLS_NAME instance;\
    return &instance;\
}\
protected:\
CLS_NAME() {}\




namespace fl
{
struct LaunchParam
{
    int viewportWidth = 800;
    int viewportHeight = 600;
    
    float clearColorR = 0.2f;
    float clearColorG = 0.3f;
    float clearColorB = 0.7f;
    
    void operator= (const LaunchParam& other)
    {
        this->viewportWidth = other.viewportWidth;
        this->viewportHeight = other.viewportHeight;
        
        this->clearColorR = other.clearColorR;
        this->clearColorG = other.clearColorG;
        this->clearColorB = other.clearColorB;
    }
};

enum class EInputKey
{
    KEY_ESC,
    
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D,
    
    KEY_Q,
    KEY_E,
    
    
    Max,
};

enum class EKeyState
{
    PRESS,
    RELEASE,
    
    Max,
};

}

