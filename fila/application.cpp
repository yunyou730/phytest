#include "application.h"
#include "framework/Framework.h"

namespace fl {

Application::Application()
{
    
}

Application::~Application()
{
    
}

void Application::OnPrepare()
{
    _framework = new Framework();
}

void Application::OnCleanup()
{
    
}

void Application::OnUpdate()
{
    
}

void Application::OnRenderer()
{
    
}

void Application::SetDeltaTime(float deltaTime)
{
    
}

float Application::GetDeltaTime()
{
    return 0.0f;
}

}
