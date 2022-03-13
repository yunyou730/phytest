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
        
//    CreatePersCamera(launchParam.viewportWidth,launchParam.viewportHeight);
    CreateOthoCamera(launchParam.viewportWidth,launchParam.viewportHeight);
    
//    CreateVBOTest();
//    CreateEBOTest();
//    CreateBox();
    CreatePhyBox();
    CreatePhyGround();
    
    /*
    
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

void Game::CreatePersCamera(int viewportWidth,int viewportHeight)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto cameraComp = new fl::CameraComponent(viewportWidth,viewportHeight);
    cameraComp->SetLookDir(glm::vec3(0,0,-1));
    
    entity->AddComponent(CLASS_NAME(CameraComponent), cameraComp);
    
    auto transformComp = entity->GetComponent<fl::TransformComponent>();
    transformComp->SetPosition(glm::vec3(0,0,5.0));
}

void Game::CreateOthoCamera(int viewportWidth,int viewportHeight)
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    auto cameraComp = new fl::CameraComponent(viewportWidth,viewportHeight);
    cameraComp->SetLookDir(glm::vec3(0,0,-1));
    cameraComp->SetCameraType(fl::ECameraType::Ortho);
    
    entity->AddComponent(CLASS_NAME(CameraComponent), cameraComp);
    
    auto transformComp = entity->GetComponent<fl::TransformComponent>();
    transformComp->SetPosition(glm::vec3(0,0,5.0));
}

void Game::CreateVBOTest()
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

void Game::CreateEBOTest()
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

void Game::CreateBox()
{
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto primComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,true);
    
    // near
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // far
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // left
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // right
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // top & bottom
    // todo
    
    primComp->SetIndexData({
        0,1,2,1,2,3,        // near
        4,5,6,5,6,7,        // far
        8,9,10,9,10,11,      // left
        12,13,14,13,14,15,  // right
        
    });
    primComp->Commit();
    
    entity->AddComponent(fl::PrimitiveComponent::ClsName(),primComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(fl::RenderStateComponent::ClsName(),renderStateComp);
    
}

void Game::CreatePhyBox()
{
    // @miao @todo
    fl::Entity* entity = GetFramework()->CreateEntity();

    
    auto primComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,true);
    
    // near
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // far
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // left
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // right
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // top & bottom
    // todo
    
    primComp->SetIndexData({
        0,1,2,1,2,3,        // near
        4,5,6,5,6,7,        // far
        8,9,10,9,10,11,      // left
        12,13,14,13,14,15,  // right
    });
    primComp->Commit();
    
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

void Game::CreatePhyGround()
{
    // @miao @todo
    fl::Entity* entity = GetFramework()->CreateEntity();
    
    auto transform = entity->GetComponent<fl::TransformComponent>();
    transform->SetPosition(glm::vec3(0,-10,-1));
    
    auto primComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,true);
    
    // near
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // far
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // left
    primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // right
    primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
    
    // top & bottom
    // todo
    
    primComp->SetIndexData({
        0,1,2,1,2,3,        // near
        4,5,6,5,6,7,        // far
        8,9,10,9,10,11,      // left
        12,13,14,13,14,15,  // right
        
    });
    primComp->Commit();
    entity->AddComponent(fl::PrimitiveComponent::ClsName(),primComp);
    
    // render state
    auto renderStateComp = new fl::RenderStateComponent();
    renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
    renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
    renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
    entity->AddComponent(fl::RenderStateComponent::ClsName(),renderStateComp);
    
    // phy 2d
    auto phy2dComp = new fl::Phy2DComponent();
    phy2dComp->SetBodyType(fl::Phy2DComponent::BodyType::Static);
    entity->AddComponent(fl::Phy2DComponent::ClsName(),phy2dComp);
}

}
