#include "Game.h"
#include "Framework.h"
#include "Entity.h"
#include "PremitiveComponent.h"

namespace ad {

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::OnPrepare(const fl::LaunchParam& launchParam)
{
    fl::Application::OnPrepare(launchParam);
    
    fl::Entity* entity = GetFramework()->CreateEntity();
//    entity->AddComponent(CLASS_NAME(), <#Component *component#>)
    
    printf("[1]%s [2]%s\n",CLASS_NAME(fl::PremitiveComponent),CLASS_NAME(PremitiveComponent));
    
//    fl::PremitiveComponent comp;
    
//    entity->AddComponent(<#const std::string &compClsName#>, <#Component *component#>)
    
    
}

void Game::OnCleanup()
{
    fl::Application::OnCleanup();
    
}

void Game::OnUpdate()
{
    fl::Application::OnUpdate();
    
}

void Game::OnRenderer()
{
    fl::Application::OnRenderer();
    
}

}
