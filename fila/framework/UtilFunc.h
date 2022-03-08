#pragma once

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

class RenderUtil
{
public:
    static void RenderPrimitive(ShaderManager* shaderManager,Entity* entity,CameraComponent* cameraComponent);
    
protected:
    static GLuint HandlePrimitiveType(RenderStateComponent* renderStateComp);
    static void HandleFillMode(RenderStateComponent* renderStateComp);
    static void HandleDepthStencilTest(RenderStateComponent* renderStateComp);
    static void HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp);

};
}
