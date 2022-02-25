#include "System.h"

namespace fl {

class Framework;
class PremitiveComponent;
class Entity;
class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Renderer() override;
        
protected:
    void RenderPremitive(Entity* entity);
};

}
