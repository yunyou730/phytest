#include "RenderFunc.h"
#include <glm/gtc/matrix_transform.hpp>

namespace fl {

/*
 Render Util
 **/
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

void RenderUtil::HandleDepthStencilTest(RenderStateComponent* renderStateComp)
{
    renderStateComp->IsEnableZTest() ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void RenderUtil::HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp)
{
    if(shader->CheckUniform("u_Model"))
    {
//        glm::mat4 model = targetTransform->GetModelMatrix();
        glm::mat4 model = CalcModelMatrix(targetTransform->_pos,targetTransform->_scale,targetTransform->_rotByEachAxis);
        shader->SetUniformMat4x4("u_Model", &model[0][0]);
    }
    HandleVP(shader,cameraTransform,cameraComp);
}

void RenderUtil::HandleVP(ShaderProgram* shader,TransformComponent* cameraTransform,CameraComponent* cameraComp)
{
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
    RenderUtil::HandleDepthStencilTest(renderStateComp);
    

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


std::vector<Entity*> RenderUtil::GetCameraEntities(Framework* framework)
{
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(CameraComponent));
    return framework->QueryEntityWithCompSet(compSet);
}

std::vector<Entity*> RenderUtil::GetRenderableEntities(Framework* framework)
{
    std::set<std::string> compSet;
    compSet.insert(CLASS_NAME(PrimitiveComponent));
    compSet.insert(CLASS_NAME(RenderStateComponent));
    
    std::vector<Entity*> renderEntities = framework->QueryEntityWithCompSet(compSet);
    return renderEntities;
}

glm::mat4 RenderUtil::CalcModelMatrix(const glm::vec3& translate,const glm::vec3& scale,glm::vec3& rotByEachAxis)
{
    glm::mat4 result(1.0);
    
    // scale part
    glm::mat4 scaleMat(1.0);
    scaleMat = glm::scale(scaleMat,scale);
    
    // rotation part
    glm::mat4 rotByX(1.0),rotByY(1.0),rotByZ(1.0);
    
    rotByX = glm::rotate(rotByX,glm::radians(rotByEachAxis.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotByY = glm::rotate(rotByY,glm::radians(rotByEachAxis.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotByZ = glm::rotate(rotByZ,glm::radians(rotByEachAxis.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    glm::mat4 rotMat = rotByX * rotByY * rotByZ;
    
    // translate part
    glm::mat4 translateMat(1.0);
    translateMat = glm::translate(translateMat,translate);
    
    
    result = scaleMat * rotMat * translateMat;
    
    return result;
}

}
