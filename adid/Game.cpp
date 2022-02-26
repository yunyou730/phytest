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
    
    // Create entity1 ,render rectangle
    {
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
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPos);
        renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
        renderStateComp->SetFillMode(fl::ERenderFillMode::Wireframe);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }

    
    
    // Create entity2
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        
        auto premitiveComp = new fl::PremitiveComponent(fl::EVertexAttrType::POS_UV);
        
        
        
    }
    
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
