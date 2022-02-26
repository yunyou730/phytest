#include "Game.h"
#include "Framework.h"
#include "Entity.h"
#include "PremitiveComponent.h"
#include "RenderStateComponent.h"

#include "fila.h"

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
    
    
    // Create one test render entity
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto premitiveComp = new fl::PremitiveComponent(fl::EVertexAttrType::POS);
    premitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0));
    premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
    premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
    
    premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
    premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
    premitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0));
    
    premitiveComp->Commit();
    entity->AddComponent(CLASS_NAME(PremitiveComponent), premitiveComp);
    
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinShader1);
    entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    
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
