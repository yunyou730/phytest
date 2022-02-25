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
    
    auto comp = new fl::PremitiveComponent(fl::EVertexAttrType::POS);
    comp->AddVertex(glm::vec3(-0.5,-0.5,0.0));
    comp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
    comp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
    comp->AddVertex(glm::vec3( 0.5, 0.5,0.0));
    
    entity->AddComponent(CLASS_NAME(PremitiveComponent), comp);

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
