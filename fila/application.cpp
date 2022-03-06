#include "application.h"
#include "framework/Framework.h"
#include "common.h"

#include "TestSystem.h"
#include "RendererSystem.h"
#include "ImGuiSystem.h"

// managers
#include "renderer/ShaderManager.h"



namespace fl {

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::OnPrepare(Window* window,const LaunchParam& launchParam)
{
    _window = window;
    
    _shaderManager = new ShaderManager();
    _framework = new Framework(this);
    
    // system
    _framework->RegisterSystem(new RendererSystem(_framework));
    _framework->RegisterSystem(new ImGuiSystem(_framework));
    
    // world component
    auto globalRenderParam = new WCGlobalRenderParam();
    globalRenderParam->launchParam = launchParam;
    
    auto keyboardInput = new WCKeyboardInput();
    
    _framework->RegisterWorldComponent(CLASS_NAME(WCGlobalRenderParam),globalRenderParam);
    _framework->RegisterWorldComponent(CLASS_NAME(WCKeyboardInput),keyboardInput);

    // Prepare
    _framework->OnPrepare(launchParam);
}

void Application::OnCleanup()
{
    _framework->OnCleanUp();
    SAFE_DEL(_framework);
    SAFE_DEL(_shaderManager);
}

void Application::OnUpdate()
{
    _framework->OnUpdate();
}

void Application::OnRenderer()
{
    _framework->OnRender();
}

void Application::ProcessInput(Window* window)
{
    auto input = _framework->GetWorldComponent<WCKeyboardInput>(CLASS_NAME(WCKeyboardInput));

    RefreshKeyState(window,input,GLFW_KEY_ESCAPE,EInputKey::KEY_ESC);
    RefreshKeyState(window,input,GLFW_KEY_UP,EInputKey::KEY_UP);
    RefreshKeyState(window,input,GLFW_KEY_DOWN,EInputKey::KEY_DOWN);
    RefreshKeyState(window,input,GLFW_KEY_LEFT,EInputKey::KEY_LEFT);
    RefreshKeyState(window,input,GLFW_KEY_RIGHT,EInputKey::KEY_RIGHT);
    RefreshKeyState(window,input,GLFW_KEY_W,EInputKey::KEY_W);
    RefreshKeyState(window,input,GLFW_KEY_S,EInputKey::KEY_S);
    RefreshKeyState(window,input,GLFW_KEY_A,EInputKey::KEY_A);
    RefreshKeyState(window,input,GLFW_KEY_D,EInputKey::KEY_D);
    RefreshKeyState(window,input,GLFW_KEY_Q,EInputKey::KEY_Q);
    RefreshKeyState(window,input,GLFW_KEY_E,EInputKey::KEY_E);
    
    
    if(input->GetState(EInputKey::KEY_ESC) == EKeyState::PRESS)
    {
        SetShouldExit();
    }
}

void Application::RefreshKeyState(Window* window,
                     WCKeyboardInput* input,
                     int glfwKeyCode,
                     EInputKey keyCode)
{
    int glfwState = glfwGetKey(window->GLFWWindow(), glfwKeyCode);
    fl::EKeyState state = (glfwState  == GLFW_PRESS) ? fl::EKeyState::PRESS : fl::EKeyState::RELEASE;
    input->SetState(keyCode, state);
}

}
