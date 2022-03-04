#pragma once
#include "window.h"

namespace fl {

class Framework;
class ShaderManager;
class Application
{
public:
    Application();
    virtual ~Application();
    
    virtual void OnPrepare(const fl::LaunchParam& launchParam);
    virtual void OnCleanup();
    
    virtual void OnUpdate();
    virtual void OnRenderer();
    
    void SetDeltaTime(float deltaTime);
    float GetDeltaTime();
    
    void SetDesireFPS(int desireFPS) { _desireFPS = desireFPS;}
    int GetDesireFPS() const { return _desireFPS;}
    
// managers
public:
    ShaderManager* GetShaderManager() { return _shaderManager;}
    
protected:
    Framework* GetFramework() { return _framework;}
    
protected:
    Framework*  _framework = nullptr;
    float       _deltaTimeThisFrame = 0.0f;
    int       _desireFPS = 60.0f;
    
// managers
    ShaderManager* _shaderManager = nullptr;
};

}

