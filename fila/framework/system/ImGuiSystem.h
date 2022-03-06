#include "System.h"
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

class ImGuiSystem : public System, public ISysRenderer,public ISysPrepare,public ISysCleanup
{
public:
    ImGuiSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;
    virtual void CleanUp() override;
};

}
