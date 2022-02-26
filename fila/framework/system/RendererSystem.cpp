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
#include "RenderStateComponent.h"
#include "application.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"

namespace fl {

RendererSystem::RendererSystem(Framework* framework)
    :System(framework)
{
    
}

void RendererSystem::Prepare(const LaunchParam& launchParam)
{
    _shaderManager = GetFramework()->GetApp()->GetShaderManager();
    
    auto param =_framework->GetWorldComponent<WCGlobalRenderParam>(CLASS_NAME(WCGlobalRenderParam));
    glClearColor(param->launchParam.clearColorR,
                 param->launchParam.clearColorG,
                 param->launchParam.clearColorB, 1.0f);
    
}

void RendererSystem::Renderer()
{
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(PremitiveComponent));
    compSet.insert(CLASS_NAME(RenderStateComponent));
    
    std::vector<Entity*> entities = GetFramework()->QueryEntityWithCompSet(compSet);
    
    for(auto it = entities.begin();it != entities.end();it++)
    {
        Entity* entity = *it;
        RenderPremitive(entity);
    }
}

void RendererSystem::RenderPremitive(Entity* entity)
{
    auto premComp = entity->GetComponent<PremitiveComponent>(CLASS_NAME(PremitiveComponent));
    auto renderStateComp = entity->GetComponent<RenderStateComponent>(CLASS_NAME(RenderStateComponent));
    
    
    unsigned int shaderId = renderStateComp->GetShaderId();
    int verticesCount = premComp->GetVerticesCount();
    GLuint vao = premComp->GetVAO();
    
    ShaderProgram* shader = _shaderManager->GetShader(shaderId);
    shader->Use();
    glBindVertexArray(vao);
    glDrawArrays(renderStateComp->GetPrimitiveType(),0,verticesCount);
    glBindVertexArray(0);
    shader->UnUse();
}


}
