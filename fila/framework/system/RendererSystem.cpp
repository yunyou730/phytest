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
    std::vector<Entity*> cameraEntities = GetCameraEntities();
    std::vector<Entity*> toRenderEntities = GetRenderableEntities();
    
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
                RenderPrimitive(entity,camComp);
            }
        }
    }
}

std::vector<Entity*> RendererSystem::GetCameraEntities()
{
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(CameraComponent));
    return GetFramework()->QueryEntityWithCompSet(compSet);
}

std::vector<Entity*> RendererSystem::GetRenderableEntities()
{
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(PrimitiveComponent));
    compSet.insert(CLASS_NAME(RenderStateComponent));
    
    std::vector<Entity*> renderEntities = GetFramework()->QueryEntityWithCompSet(compSet);
    return renderEntities;
}

void RendererSystem::RenderPrimitive(Entity* entity,CameraComponent* cameraComponent)
{
    auto primComp = entity->GetComponent<PrimitiveComponent>();
    auto renderStateComp = entity->GetComponent<RenderStateComponent>();
    auto targetTransform = entity->GetComponent<TransformComponent>();
    auto cameraTransform = cameraComponent->GetEntity()->GetComponent<TransformComponent>();
    
    // params
    unsigned int shaderId = renderStateComp->GetShaderId();
    GLuint vao = primComp->GetVAO();
    assert(vao != 0);
    
    GLuint primitiveType = HandlePrimitiveType(renderStateComp);
    HandleFillMode(renderStateComp);
    
    ShaderProgram* shader = _shaderManager->GetShader(shaderId);
    shader->Use();
    
    HandleMVP(shader,targetTransform,cameraTransform,cameraComponent);
    
    glBindVertexArray(vao);

    if(primComp->IsEBOEnable())
    {
        glDrawElements(primitiveType,primComp->GetIndicesCount(),GL_UNSIGNED_INT,0);
    }
    else
    {
        glDrawArrays(primitiveType,0,primComp->GetVerticesCount());
    }
    glBindVertexArray(0);
    shader->UnUse();
}

GLuint RendererSystem::HandlePrimitiveType(RenderStateComponent* renderStateComp)
{
    auto primitiveType = renderStateComp->GetPrimitiveType();
    
    GLuint result = GL_TRIANGLES;
    switch(primitiveType)
    {
        case ERenderPrimitiveType::Triangle:
            result = GL_TRIANGLES;
            break;
        case ERenderPrimitiveType::Point:
            result = GL_POINTS;
            glPointSize(renderStateComp->GetPointSize());
            break;
        default:
            result = GL_TRIANGLES;
            break;
    }
    return result;
}

void RendererSystem::HandleFillMode(RenderStateComponent* renderStateComp)
{
    switch(renderStateComp->GetFillMode())
    {
        case ERenderFillMode::Fill:
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
        case ERenderFillMode::Wireframe:
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            break;
        default:
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            break;
    }
}

void RendererSystem::HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp)
{
    if(shader->CheckUniform("u_Model"))
    {
        glm::mat4 model = targetTransform->GetModelMatrix();
        shader->SetUniformMat4x4("u_Model", &model[0][0]);
    }
    
    if(shader->CheckUniform("u_View"))
    {
        glm::mat4 view = cameraComp->GetViewMatrix(cameraTransform->GetPos());
        
//        fl::Log::Info(view);
        shader->SetUniformMat4x4("u_View", &view[0][0]);
    }
    
    if(shader->CheckUniform("u_Projection"))
    {
        glm::mat4 projection = cameraComp->GetProjectionMatrix();
        
        fl::Log::Info(projection);
        shader->SetUniformMat4x4("u_Projection",&projection[0][0]);
    }
}

}
