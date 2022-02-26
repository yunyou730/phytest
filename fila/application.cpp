#include "application.h"
#include "framework/Framework.h"
#include "common.h"

#include "TestSystem.h"
#include "RendererSystem.h"

#include "WorldComponent.h"

// managers
#include "renderer/ShaderManager.h"

namespace fl {

Application::Application()
{

}

Application::~Application()
{

}

void Application::OnPrepare(const LaunchParam& launchParam)
{
    _shaderManager = new ShaderManager();
    _framework = new Framework(this);
    
    // system
    _framework->RegisterSystem(new RendererSystem(_framework));
    
    // world component
    auto globalRenderParam = new WCGlobalRenderParam();
    globalRenderParam->launchParam = launchParam;
    
    _framework->RegisterWorldComponent(CLASS_NAME(WCGlobalRenderParam),globalRenderParam);
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

void Application::SetDeltaTime(float deltaTime)
{
    
}

float Application::GetDeltaTime()
{
    return 0.0f;
}

}
