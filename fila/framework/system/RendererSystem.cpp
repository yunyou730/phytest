#include "RendererSystem.h"
#include "log.h"
#include "common.h"
#include "WorldComponent.h"
#include <glad/glad.h>
#include "Framework.h"
#include <set>
#include <string>
#include "Entity.h"
#include "PremitiveComponent.h"

namespace fl {

RendererSystem::RendererSystem(Framework* framework)
    :System(framework)
{
    
}

void RendererSystem::Prepare(const LaunchParam& launchParam)
{
    auto param =_framework->GetWorldComponent<WCGlobalRenderParam>(CLASS_NAME(WCGlobalRenderParam));
    glClearColor(param->launchParam.clearColorR,
                 param->launchParam.clearColorG,
                 param->launchParam.clearColorB, 1.0f);
}

void RendererSystem::Renderer()
{
//    Log::Info(__FUNCTION__);
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(PremitiveComponent));
    
    std::vector<Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Entity* entity = *it;
        RenderPremitive(entity);
    }
}


void RendererSystem::RenderPremitive(Entity* entity)
{
    PremitiveComponent* premComp = entity->GetComponent<PremitiveComponent>(CLASS_NAME(PremitiveComponent));
    
    // @miao @todo
    
}


}
