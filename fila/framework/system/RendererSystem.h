#include "System.h"
#include "RenderStateComponent.h"
#include <vector>

namespace fl {

class Framework;
class Entity;
class PrimitiveComponent;
class CameraComponent;
class TransformComponent;
class CameraComponent;

class ShaderManager;
class ShaderProgram;

class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;
    
protected:
    std::vector<Entity*> GetCameraEntities();
    std::vector<Entity*> GetRenderableEntities();
    
    void RenderPrimitive(Entity* entity,CameraComponent* camComp);
    GLuint HandlePrimitiveType(RenderStateComponent* renderStateComp);
    void HandleFillMode(RenderStateComponent* renderStateComp);
    void HandleMVP(ShaderProgram* shader,TransformComponent* targetTransform,TransformComponent* cameraTransform,CameraComponent* cameraComp);
    
protected:
    ShaderManager*  _shaderManager = nullptr;
};

}
