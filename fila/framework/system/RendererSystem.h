#include "System.h"

namespace fl {

class RendererSystem : public System, public ISysRenderer,public ISysPrepare
{
public:
    virtual void Prepare() override;
    virtual void Renderer() override;
};

}
