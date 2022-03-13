#include "System.h"
#include "RenderStateComponent.h"
#include <vector>
#include <set>
#include "box2d.h"
#include "WorldComponent.h"
#include "ShaderManager.h"

namespace fl {
    
class Phy2DSystem : public System,public ISysUpdate,public ISysPrepare,public ISysRenderer
{
public:
    Phy2DSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void Update() override;
    virtual void Renderer() override;
    
protected:
    void ProcessTickRate();
    void OnPhyTick();
    void CheckAndCreateBody();
    void SyncPhyPropToTransform();
    
protected:
    b2World*            _world = nullptr;
    WCPhy2DSettings*    _phy2dSettings = nullptr;
    float               _timeCounter = 0.f;
    
    std::set<std::string>   _compSetWithPhy2d;
    
    ShaderManager*  _shaderManager = nullptr;
};

}
