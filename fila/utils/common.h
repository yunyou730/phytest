#pragma once

#define SAFE_DEL(pointer) {\
if(pointer != nullptr) \
{\
    delete pointer;\
    pointer = nullptr;\
}\
}\

#define CLASS_NAME(name) #name


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
}

