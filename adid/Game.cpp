#include "Game.h"
#include "Framework.h"
#include "Entity.h"
#include "PrimitiveComponent.h"
#include "RenderStateComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "fila.h"

#include "CameraCtrlSystem.h"

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
    
    GetFramework()->RegisterSystem(new CameraCtrlSystem(GetFramework()));
        
    CreateCamera(launchParam.viewportWidth,launchParam.viewportHeight);
    CreateTest1();
    CreateTest2();
    
    /*
    // Create entity1 ,render rectangle
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        
        auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS);
        primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0));
        primitiveComp->Commit();
        entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
        
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPos);
        renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
        renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    // Create entity2
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV);
        primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1));
        primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1));
        
        primitiveComp->Commit();
        
        entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
        
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPosUV);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    // Create entity3
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR);
        primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(0,0,0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(1,0,0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,1,0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(1,0,0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,1,0));
        primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,1));
        
        primitiveComp->Commit();
        
        entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
        
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::BuiltinAttrPosUVCol);
        entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    }
    
    
    // Create entity4
    {
        fl::Entity* entity = GetFramework()->CreateEntity();
        auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS);
        primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0));
        primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0));
        primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0));
        
        primitiveComp->Commit();
        
        entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
        
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

void Game::CreateCamera(int viewportWidth,int viewportHeight)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto cameraComp = new fl::CameraComponent(viewportWidth,viewportHeight);
    cameraComp->SetLookDir(glm::vec3(0,0,1));
    cameraComp->SetCameraType(fl::ECameraType::Ortho);
    
    entity->AddComponent(CLASS_NAME(CameraComponent), cameraComp);
    
    auto transformComp = entity->GetComponent<fl::TransformComponent>();
    transformComp->SetPosition(glm::vec3(0,0,-5.0));
}

void Game::CreateTest1()
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto transform = entity->GetComponent<fl::TransformComponent>();
    transform->SetScale(glm::vec3(1.0,1.2,1.0));
    transform->SetPosition(glm::vec3(0.0,0.0,0.0));
    
    // primitve
    auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,false);
    primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(1,0,0));
    primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
    primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
    
    primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
    primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
    primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,0));
    
    primitiveComp->Commit();
    entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
}

void Game::CreateTest2()
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto transform = entity->GetComponent<fl::TransformComponent>();
    transform->SetScale(glm::vec3(1.5,0.2,2.0));
    transform->SetPosition(glm::vec3(0,0.0,0.0));
    
    auto primitiveComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,true);
    primitiveComp->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(1,0,0));
    primitiveComp->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
    primitiveComp->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
    primitiveComp->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,0));
    primitiveComp->SetIndexData({0,1,2,1,3,2});
    primitiveComp->Commit();
    entity->AddComponent(CLASS_NAME(PrimitiveComponent), primitiveComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(CLASS_NAME(RenderStateComponent),renderStateComp);
    
    
}

}
