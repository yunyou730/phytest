#include "System.h"

namespace fl {

class Framework;
class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    RendererSystem(Framework* framework);
    
    virtual void Prepare(const PrepareParam& prepareParam) override;
    virtual void Renderer() override;
};

}
