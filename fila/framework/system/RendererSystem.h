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
class WCGlobalRenderParam;

class RendererSystem : public System, public ISysRenderer,public ISysPrepare,public ISysUpdate
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Update() override;
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;

protected:
    ShaderManager*  _shaderManager = nullptr;
    WCGlobalRenderParam*    _renderParam = nullptr;
};

}
