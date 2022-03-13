#include "RendererSystem.h"
#include "log.h"
#include "common.h"
#include "WorldComponent.h"
#include <glad/glad.h>
#include "Framework.h"
#include <set>
#include <string>

#include "Entity.h"
#include "PrimitiveComponent.h"
#include "RenderStateComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "application.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"


#include "RenderFunc.h"

namespace fl {

RendererSystem::RendererSystem(Framework* framework)
    :System(framework)
{
    
}

void RendererSystem::Prepare(const LaunchParam& launchParam)
{
    _shaderManager = GetFramework()->GetApp()->GetShaderManager();
    _renderParam =_framework->GetWorldComponent<WCGlobalRenderParam>();
    
    auto param =_framework->GetWorldComponent<WCGlobalRenderParam>();
    glClearColor(param->launchParam.clearColorR,
                 param->launchParam.clearColorG,
                 param->launchParam.clearColorB, 1.0f);
    
}

void RendererSystem::Update()
{
    if(_renderParam->bLaunchParamDirty)
    {
        _renderParam->bLaunchParamDirty = false;
        std::vector<Entity*> cameraEntities = RenderUtil::GetCameraEntities(GetFramework());
        for(auto it = cameraEntities.begin();it != cameraEntities.end();it++)
        {
            auto camComp = (*it)->GetComponent<CameraComponent>();
            camComp->SetViewportSize(_renderParam->launchParam.viewportWidth,_renderParam->launchParam.viewportHeight);
            
        }
    }
}

void RendererSystem::Renderer()
{
    std::vector<Entity*> cameraEntities = RenderUtil::GetCameraEntities(GetFramework());
    std::vector<Entity*> toRenderEntities = RenderUtil::GetRenderableEntities(GetFramework());
    
    // Each camera renders each entity.
    for(auto camIt = cameraEntities.begin();camIt != cameraEntities.end();camIt++)
    {
        auto camComp = (*camIt)->GetComponent<CameraComponent>();
        for(auto it = toRenderEntities.begin();it != toRenderEntities.end();it++)
        {
            Entity* entity = *it;
            RenderStateComponent* renderStateComp = entity->GetComponent<RenderStateComponent>();
            if(camComp->CheckLayer(renderStateComp->GetRenderLayer()))
            {
                RenderUtil::RenderPrimitive(_shaderManager,entity,camComp);
            }
        }
    }
}

}
