#pragma once

#include <glad/glad.h>
#include "Framework.h"
#include <set>
#include <string>
//#include "glm.hpp"

#include "Entity.h"
#include "PrimitiveComponent.h"
#include "RenderStateComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

#include "application.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"


namespace fl {

class RenderUtil
{
    friend class Phy2dFunc;
public:
    static void RenderPrimitive(ShaderManager* shaderManager,Entity* entity,CameraComponent* cameraComponent);
    static std::vector<Entity*> GetCameraEntities(Framework* framework);
    static std::vector<Entity*> GetRenderableEntities(Framework* framework);
    static glm::mat4 CalcModelMatrix(const glm::vec3& translate,const glm::vec3& scale,glm::vec3& rotByEachAxis);
    
protected:
    static GLuint HandlePrimitiveType(RenderStateComponent* renderStateComp);
    static void HandleFillMode(RenderStateComponent* renderStateComp);
    static void HandleDepthStencilTest(RenderStateComponent* renderStateComp);
    static void HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp);
    static void HandleVP(ShaderProgram* shader,TransformComponent* cameraTransform,CameraComponent* cameraComp);
    

};

}
