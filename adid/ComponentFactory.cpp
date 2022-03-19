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
        fl::Log::Info(fl::PrimitiveComponent::ClsName());
        
        
    }
    else if(strcmp(compName,fl::RenderStateComponent::ClsName()) == 0)
    {
        fl::Log::Info(fl::RenderStateComponent::ClsName());
    }
    else if(strcmp(compName,fl::Phy2DComponent::ClsName()) == 0)
    {
        fl::Log::Info(fl::Phy2DComponent::ClsName());
    }
    
    return comp;
}

}
