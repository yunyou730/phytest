#include "application.h"
#include "framework/Framework.h"
#include "common.h"

#include "TestSystem.h"
#include "RendererSystem.h"
#include "ImGuiSystem.h"
#include "Phy2DSystem.h"

#include "ShaderManager.h"
#include "PrimitiveManager.h"

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
    
    _shaderManager = ShaderManager::Instance();
    _primitiveManager = PrimitiveManager::Instance();
    _framework = new Framework(this);
    
    
    // managers
    _shaderManager->StartUp();
    _primitiveManager->StartUp();
    // @miao @todo
    
    // framework
    // system
    _framework->RegisterSystem(new RendererSystem(_framework));
    _framework->RegisterSystem(new ImGuiSystem(_framework));
    _framework->RegisterSystem(new Phy2DSystem(_framework));
    
    // world component
    auto globalRenderParam = new WCGlobalRenderParam();
    globalRenderParam->launchParam = launchParam;
    
    _framework->RegisterWorldComponent(WCGlobalRenderParam::ClsName(),globalRenderParam);
    _framework->RegisterWorldComponent(WCKeyboardInput::ClsName(),new WCKeyboardInput());
    _framework->RegisterWorldComponent(WCPhy2DSettings::ClsName(),new WCPhy2DSettings());
    _framework->RegisterWorldComponent(WCImGUISettings::ClsName(),new WCImGUISettings());
    
    // Prepare
    _framework->OnPrepare(launchParam);
}

void Application::OnCleanup()
{
    _framework->OnCleanUp();
    SAFE_DEL(_framework);
//    SAFE_DEL(_shaderManager);
//    SAFE_DEL(_primitiveManager);;
}

void Application::OnUpdate()
{
    _framework->OnUpdate();
}

void Application::OnLateUpdate()
{
    
}

void Application::OnRenderer()
{
    _framework->OnRender();
}

void Application::ProcessInput(Window* window)
{
    auto input = _framework->GetWorldComponent<WCKeyboardInput>();

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

void Application::OnViewportSizeChange(int width,int height)
{
    WCGlobalRenderParam* renderParam = _framework->GetWorldComponent<WCGlobalRenderParam>();
    renderParam->bLaunchParamDirty = true;
    renderParam->launchParam.viewportWidth = width;
    renderParam->launchParam.viewportHeight = height;
}

}
