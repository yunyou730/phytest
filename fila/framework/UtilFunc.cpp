#include "UtilFunc.h"

namespace fl {
GLuint RenderUtil::HandlePrimitiveType(RenderStateComponent* renderStateComp)
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

void RenderUtil::HandleFillMode(RenderStateComponent* renderStateComp)
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

void RenderUtil::HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp)
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
        
//        fl::Log::Info(projection);
        shader->SetUniformMat4x4("u_Projection",&projection[0][0]);
    }
}

void RenderUtil::RenderPrimitive(ShaderManager* shaderManager,Entity* entity,CameraComponent* cameraComponent)
{
    auto primComp = entity->GetComponent<PrimitiveComponent>();
    auto renderStateComp = entity->GetComponent<RenderStateComponent>();
    auto targetTransform = entity->GetComponent<TransformComponent>();
    auto cameraTransform = cameraComponent->GetEntity()->GetComponent<TransformComponent>();

    // params
    unsigned int shaderId = renderStateComp->GetShaderId();
    GLuint vao = primComp->GetVAO();
    assert(vao != 0);

    GLuint primitiveType = RenderUtil::HandlePrimitiveType(renderStateComp);
    RenderUtil::HandleFillMode(renderStateComp);

    ShaderProgram* shader = shaderManager->GetShader(shaderId);
    shader->Use();

    RenderUtil::HandleMVP(shader,targetTransform,cameraTransform,cameraComponent);

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

}
