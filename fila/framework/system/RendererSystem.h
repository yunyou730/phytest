#include "System.h"
#include "RenderStateComponent.h"

namespace fl {

class Framework;
class PremitiveComponent;
class Entity;
class ShaderManager;
class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;
        
protected:
    void RenderPremitive(Entity* entity);
    
    GLuint HandlePrimitiveType(RenderStateComponent* renderStateComp);
    void HandleFillMode(RenderStateComponent* renderStateComp);
    
protected:
    ShaderManager*  _shaderManager = nullptr;
};

}
