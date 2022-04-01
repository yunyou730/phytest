#include "Game.h"
#include "Framework.h"
#include "Entity.h"


#include "PrimitiveComponent.h"
#include "RenderStateComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Phy2DComponent.h"

#include "fila.h"

#include "CameraCtrlSystem.h"
#include "TestMoveSystem.h"
#include "HierarchyGUISystem.h"
#include "InspectorGuiSystem.h"
#include "DebugGuiSystem.h"
#include "TestSystem.h"

#include "WorldComp.h"

namespace ad {

Game::Game()
{
    
}

Game::~Game()
{
    
}

void Game::OnPrepare(fl::Window* window,const fl::LaunchParam& launchParam)
{
    fl::Application::OnPrepare(window,launchParam);
    
    GetFramework()->RegisterWorldComponent(WCEntitySelection::ClsName(), new WCEntitySelection());
    
    GetFramework()->RegisterSystem(new CameraCtrlSystem(GetFramework()));
    GetFramework()->RegisterSystem(new TestMoveSystem(GetFramework()));
    GetFramework()->RegisterSystem(new HierarychyGUISystem(GetFramework()));
    GetFramework()->RegisterSystem(new InspectorGuiSystem(GetFramework()));
    GetFramework()->RegisterSystem(new DebugGuiSystem(GetFramework()));
    GetFramework()->RegisterSystem(new TestSystem(GetFramework()));
        
//    CreatePersCamera(launchParam.viewportWidth,launchParam.viewportHeight);
    CreateOrthoCamera(launchParam.viewportWidth,launchParam.viewportHeight);
    
    CreateBox();
    
    CreatePhyBox(glm::vec3(0,3,0));
    CreatePhyBox(glm::vec3(0,20,0));
    CreatePhyBox(glm::vec3(-5,10,0));
    
    CreatePhyGround(glm::vec3(0,0,0),{b2Vec2(0.0,0.0),b2Vec2(0.0,1.0),b2Vec2(1.0,1.0)});
    CreatePhyGround(glm::vec3(-2,2,0),{b2Vec2(0.0,0.0),b2Vec2(0.0,1.0),b2Vec2(1.0,0.0)});
    CreatePhyGround(glm::vec3( 3,2,0));
    
    
    CreatePhyGround(glm::vec3(0,-3,0),{b2Vec2(-10,-3),b2Vec2(10,-3),b2Vec2(-10,-2),b2Vec2(10,-2)});
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

void Game::CreatePersCamera(int viewportWidth,int viewportHeight)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto cameraComp = new fl::CameraComponent(viewportWidth,viewportHeight);
    cameraComp->SetLookDir(glm::vec3(0,0,-1));
    cameraComp->SetDrawDebugInfo(true);
    
    entity->AddComponent(CLASS_NAME(CameraComponent), cameraComp);
    
    auto transformComp = entity->GetComponent<fl::TransformComponent>();
    transformComp->SetPosition(glm::vec3(0,0,5.0));
}

void Game::CreateOrthoCamera(int viewportWidth,int viewportHeight)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto cameraComp = new fl::CameraComponent(viewportWidth,viewportHeight);
    cameraComp->SetLookDir(glm::vec3(0,0,-1));
    cameraComp->SetCameraType(fl::ECameraType::Ortho);
    cameraComp->SetOrthoHalf(6);
    cameraComp->SetDrawDebugInfo(true);
    
    entity->AddComponent(fl::CameraComponent::ClsName(), cameraComp);
    
    auto transformComp = entity->GetComponent<fl::TransformComponent>();
    transformComp->SetPosition(glm::vec3(0,0,5.0));
}


void Game::CreateBox()
{
    fl::Entity* entity = GetFramework()->CreateEntity();

    auto primComp = new fl::PrimitiveComponent(fl::EPrimitiveType::Quad);
    entity->AddComponent(fl::PrimitiveComponent::ClsName(),primComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(fl::RenderStateComponent::ClsName(),renderStateComp);
    
}

void Game::CreatePhyBox(const glm::vec3& pos)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto transform = entity->GetComponent<fl::TransformComponent>();
    transform->SetPosition(pos);
    
    auto primComp = new fl::PrimitiveComponent(fl::EPrimitiveType::Cube);
    entity->AddComponent(fl::PrimitiveComponent::ClsName(),primComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(fl::RenderStateComponent::ClsName(),renderStateComp);
    
    // phy 2d
    auto phy2dComp = new fl::Phy2DComponent();
    phy2dComp->SetBodyType(fl::Phy2DComponent::BodyType::Dynamic);
    entity->AddComponent(fl::Phy2DComponent::ClsName(),phy2dComp);
}

fl::Entity* Game::CreatePhyGround(const glm::vec3& pos)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto transform = entity->GetComponent<fl::TransformComponent>();
    transform->SetPosition(pos);
    
    // phy 2d
    auto phy2dComp = new fl::Phy2DComponent();
    phy2dComp->SetBodyType(fl::Phy2DComponent::BodyType::Static);
    entity->AddComponent(fl::Phy2DComponent::ClsName(),phy2dComp);
    
    return entity;
}

fl::Entity* Game::CreatePhyGround(const glm::vec3& pos,const std::vector<b2Vec2>& polygonPoints)
{
    fl::Entity* entity = CreatePhyGround(pos);
    auto phy2d = entity->GetComponent<fl::Phy2DComponent>();
    phy2d->SetPolygonShapePoints(polygonPoints);
    return entity;
}

}
