#pragma once
#include "window.h"
#include "WorldComponent.h"

namespace fl {

class Framework;
class ShaderManager;
class Window;
class Application
{
public:
    Application();
    virtual ~Application();
    
    virtual void OnPrepare(Window* window,const fl::LaunchParam& launchParam);
    virtual void OnCleanup();
    
    virtual void OnUpdate();
    virtual void OnRenderer();
    
    virtual void ProcessInput(Window* window);
    
    void SetDeltaTime(float deltaTime) { _deltaTimeThisFrame = deltaTime; }
    float GetDeltaTime() const { return _deltaTimeThisFrame;}
    
    void SetDesireFPS(int desireFPS) { _desireFPS = desireFPS;}
    int GetDesireFPS() const { return _desireFPS;}
    
    void SetShouldExit() {_bShallExit = true;}
    bool ShallExit() const { return _bShallExit; }
    
    Window* GetWindow() { return _window; }
    
// managers
public:
    ShaderManager* GetShaderManager() { return _shaderManager;}
    
protected:
    Framework* GetFramework() { return _framework;}
    void RefreshKeyState(Window* window,
                         WCKeyboardInput* input,
                         int glfwKeyCode,
                         EInputKey keyCode);
    
protected:
    Framework*  _framework = nullptr;
    float       _deltaTimeThisFrame = 0.0f;
    int         _desireFPS = 60.0f;
    
    bool        _bShallExit = false;
    
// managers
    ShaderManager* _shaderManager = nullptr;
    
    Window* _window = nullptr;
};

}

