#include "ComponentFactory.h"
#include "log.h"

#include "Entity.h"
#include "Component.h"
#include "WorldComponent.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "PrimitiveComponent.h"
#include "RenderStateComponent.h"
#include "Phy2DComponent.h"

namespace ad
{

fl::Component* ComponentFactory::CreateComponent(const char* compName,fl::Entity* entity)
{
    fl::Component* comp = nullptr;
    if(strcmp(compName,fl::TransformComponent::ClsName()) == 0)
    {
        fl::Log::Info(fl::TransformComponent::ClsName());
    }
    else if(strcmp(compName,fl::CameraComponent::ClsName()) == 0)
    {
        auto renderParam = entity->GetFramework()->GetWorldComponent<fl::WCGlobalRenderParam>();
        
        auto cameraComp = new fl::CameraComponent(renderParam->launchParam.viewportWidth,
                                                  renderParam->launchParam.viewportHeight);
        cameraComp->SetLookDir(glm::vec3(0,0,-1));
        cameraComp->SetDrawDebugInfo(true);
        entity->AddComponent(fl::CameraComponent::ClsName(), cameraComp);
    }
    else if(strcmp(compName,fl::PrimitiveComponent::ClsName()) == 0)
    {
//        auto primComp = new fl::PrimitiveComponent(fl::EVertexAttrType::POS_UV_COLOR,true);
        auto primComp = nullptr;
        
        // near
//        primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
//        primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
//        primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
//        primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
//
//        // far
//        primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
//        primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
//        primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
//        primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
//
//        // left
//        primComp->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
//        primComp->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
//        primComp->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
//        primComp->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));
//
//        // right
//        primComp->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
//        primComp->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
//        primComp->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
//        primComp->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));
//
//        // top & bottom
//        // todo
//
//        primComp->SetIndexData({
//            0,1,2,1,2,3,        // near
//            4,5,6,5,6,7,        // far
//            8,9,10,9,10,11,      // left
//            12,13,14,13,14,15,  // right
//
//        });
//        primComp->Commit();
        
        entity->AddComponent(fl::PrimitiveComponent::ClsName(),primComp);
    }
    else if(strcmp(compName,fl::RenderStateComponent::ClsName()) == 0)
    {
        fl::Log::Info(fl::RenderStateComponent::ClsName());
        
        // render state
        auto renderStateComp = new fl::RenderStateComponent();
        renderStateComp->SetShaderId((unsigned int)fl::EBuiltinShaderId::Builtin_StardardMVP);
        renderStateComp->SetPrimitiveType(fl::ERenderPrimitiveType::Triangle);
        renderStateComp->SetFillMode(fl::ERenderFillMode::Fill);
        entity->AddComponent(fl::RenderStateComponent::ClsName(),renderStateComp);
    }
    else if(strcmp(compName,fl::Phy2DComponent::ClsName()) == 0)
    {
        fl::Log::Info(fl::Phy2DComponent::ClsName());

        // phy 2d
        auto phy2dComp = new fl::Phy2DComponent();
        phy2dComp->SetBodyType(fl::Phy2DComponent::BodyType::Dynamic);
        entity->AddComponent(fl::Phy2DComponent::ClsName(),phy2dComp);
    }
    
    return comp;
}

}
