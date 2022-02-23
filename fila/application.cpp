#include "application.h"
#include "framework/Framework.h"
#include "common.h"

#include "TestSystem.h"
#include "RendererSystem.h"

#include "WorldComponent.h"

namespace fl {

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::OnPrepare(const PrepareParam& prepareParam)
{
    _framework = new Framework();
    
    // system
    _framework->RegisterSystem(new RendererSystem(_framework));
    
    // world component
    auto globalRenderParam = new WCGlobalRenderParam();
    globalRenderParam->prepareParam = prepareParam;
    
    _framework->RegisterWorldComponent(CLASS_NAME(WCGlobalRenderParam),globalRenderParam);
    _framework->OnPrepare(prepareParam);
}

void Application::OnCleanup()
{
    _framework->OnCleanUp();
    SAFE_DEL(_framework);
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
