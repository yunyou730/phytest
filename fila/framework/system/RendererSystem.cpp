#include "RendererSystem.h"
#include "log.h"
#include "common.h"
#include "WorldComponent.h"
#include <glad/glad.h>
#include "Framework.h"

namespace fl {

RendererSystem::RendererSystem(Framework* framework)
    :System(framework)
{
    
}

void RendererSystem::Prepare(const PrepareParam& prepareParam)
{
    auto param =_framework->GetWorldComponent<WCGlobalRenderParam>(CLASS_NAME(WCGlobalRenderParam));
    glClearColor(param->prepareParam.clearColorR,
                 param->prepareParam.clearColorG,
                 param->prepareParam.clearColorB, 1.0f);
}

void RendererSystem::Renderer()
{
//    Log::Info(__FUNCTION__);
}



}
