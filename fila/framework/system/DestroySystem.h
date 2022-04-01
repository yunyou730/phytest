#include "System.h"
#include "RenderStateComponent.h"
#include <vector>

namespace fl {

class Entity;
class WCDestroy;
class DestroySystem : public System,public ISysPrepare,public ISysLateUpdate
{
public:
    DestroySystem(Framework* framework);
 
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void LateUpdate() override;
    
protected:
    WCDestroy*  _destroy = nullptr;
};

}
