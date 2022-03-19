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

class WCImGUISettings;

class ImGuiSystem : public System,public ISysPrepare,public ISysCleanup,public ISysGUISupport,public ISysGUI
{
public:
    ImGuiSystem(Framework* framework);
    
    virtual void Prepare(const LaunchParam& launchParam) override;
    virtual void CleanUp() override;
    
    virtual void BeforeGUI() override;
    virtual void AfterGUI() override;
    virtual void OnGUI() override;
    
    void ToggleDebug() { _bEnableDebug = !_bEnableDebug;}
    
protected:
    bool                _bEnableDebug = false;
    WCImGUISettings*    _imguiSettings = nullptr;
};

}
