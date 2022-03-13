#include "System.h"
#include "RenderStateComponent.h"
#include <vector>
#include "box2d.h"
#include "WorldComponent.h"

namespace fl {
    
class Phy2DSystem : public System,public ISysUpdate,public ISysPrepare
{
public:
    Phy2DSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Update() override;
    
protected:
    void ProcessTickRate();
    void OnPhyTick();
    void CheckAndCreateBody();
    void SyncPhyPropToTransform();
    
protected:
    b2World*            _world = nullptr;
    WCPhy2DSettings*    _phy2dSettings = nullptr;
    float       _timeCounter = 0.f;
};

}
