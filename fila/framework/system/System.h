#pragma once
#include "window.h"

namespace fl {

class Framework;
class System
{
public:
    System(Framework* framework);
    virtual ~System();
    
    Framework* GetFramework() { return _framework;}
    
protected:
    Framework* _framework = nullptr;
};

// Prepare ----------
class ISysPrepare
{
public:
    virtual void Prepare(const LaunchParam& launchParam) = 0;
};

// Update ----------
class ISysUpdate
{
public:
    virtual void Update() = 0;
};

// Renderer ----------
class ISysRenderer
{
public:
    virtual void Renderer() = 0;
};

// Cleanup ----------
class ISysCleanup
{
public:
    virtual void CleanUp() = 0;
};

}
