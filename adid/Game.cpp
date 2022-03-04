#include "Game.h"
#include "Framework.h"
#include "Entity.h"
#include "PremitiveComponent.h"
#include "RenderStateComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

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
    
    // Create camera entity
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto cameraComp = new fl::CameraComponent(launchParam.viewportWidth,launchParam.viewportHeight);
        entity->AddComponent(CLASS_NAME(CameraComponent), cameraComp);
        
        auto transformComp = entity->GetComponent<fl::TransformComponent>(CLASS_NAME(TransformComponent));
        transformComp->SetPosition(glm::vec3(0,0,-5.0));
    }
    
    {
        // Create entity with MVP
        fl::Entity* entity = GetFramework()->CreateEntity();
        
        auto transform = entity->GetComponent<fl::TransformComponent>(CLASS_NAME(TransformComponent));
        transform->SetScale(glm::vec3(1.0,1.2,1.0));
//        transform->SetRotationZ(45);
        transform->SetPosition(glm::vec3(0.0,0.0,0.0));
        
        // primitve
        auto premitiveComp = new fl::PremitiveComponent(fl::EVertexAttrType::POS_UV_COLOR);
        premitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(1,0,0));
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
        
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
        premitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,0));
        
        premitiveComp->Commit();
        entity->AddComponent(CLASS_NAME(PremitiveComponent), premitiveComp);
        
        // render state
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
        renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
        renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    /*
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
        renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    // Create entity2
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto premitiveComp = new fl::PremitiveComponent(fl::EVertexAttrType::POS_UV);
        premitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0));
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1));
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1));
        premitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1));
        
        premitiveComp->Commit();
        
        entity->AddComponent(CLASS_NAME(PremitiveComponent), premitiveComp);
        
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPosUV);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    // Create entity3
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto premitiveComp = new fl::PremitiveComponent(fl::EVertexAttrType::POS_UV_COLOR);
        premitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(0,0,0));
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(1,0,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,1,0));
        premitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(1,0,0));
        premitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,1,0));
        premitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,1));
        
        premitiveComp->Commit();
        
        entity->AddComponent(CLASS_NAME(PremitiveComponent), premitiveComp);
        
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPosUVCol);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    
    // Create entity4
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
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinStardardBase);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    */
    
    
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
