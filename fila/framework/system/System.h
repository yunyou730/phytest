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
    Framework*  _framework = nullptr;
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

// LateUpdate ------
class ISysLateUpdate
{
public:
    virtual void LateUpdate() = 0;
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

// Before render
class ISysGUISupport
{
public:
    virtual void BeforeGUI() = 0;
    virtual void AfterGUI() = 0;
};

// GUI
class ISysGUI
{
public:
    virtual void OnGUI() = 0;
};

}
