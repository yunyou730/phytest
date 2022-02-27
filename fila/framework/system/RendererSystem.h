#include "System.h"
#include "RenderStateComponent.h"
#include <vector>

namespace fl {

class Framework;
class PremitiveComponent;
class Entity;
class ShaderManager;
class CameraComponent;
class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;
    
protected:
    std::vector<Entity*> GetCameraEntities();
    std::vector<Entity*> GetRenderableEntities();
    
    void RenderPremitive(Entity* entity,CameraComponent* camComp);
    GLuint HandlePrimitiveType(RenderStateComponent* renderStateComp);
    void HandleFillMode(RenderStateComponent* renderStateComp);
    
protected:
    ShaderManager*  _shaderManager = nullptr;
};

}
