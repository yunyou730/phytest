#include "Framework.h"
#include "system/System.h"

#define RegisterSysByType(sys,SysType,Container) ({\
auto item = dynamic_cast<SysType*>(sys);\
if(item != nullptr)\
{\
    Container.push_back(item);\
}\
})\

namespace fl {

Framework::Framework()
{
    
}

Framework::~Framework()
{
    
}

void Framework::RegisterSystem(System* sys)
{
    RegisterSysByType(sys,ISysPrepare,_prepareSysList);
    RegisterSysByType(sys,ISysUpdate,_updateSysList);
    RegisterSysByType(sys,ISysRenderer,_renderSysList);
    RegisterSysByType(sys,ISysCleanup,_cleanupSysList);
}

void Framework::RegisterWorldComponent(const std::string& wcClsName,WorldComponent* comp)
{
    auto it = _worldCompMap.find(wcClsName);
    assert(it == _worldCompMap.end());
    _worldCompMap.insert(std::make_pair(wcClsName,comp));
}

void Framework::OnPrepare(const PrepareParam& prepareParam)
{
    for(auto it = _prepareSysList.begin();it != _prepareSysList.end();it++)
    {
        (*it)->Prepare(prepareParam);
    }
}

void Framework::OnUpdate()
{
    for(auto it = _updateSysList.begin();it != _updateSysList.end();it++)
    {
        (*it)->Update();
    }
}

void Framework::OnRender()
{
    for(auto it = _renderSysList.begin();it != _renderSysList.end();it++)
    {
        (*it)->Renderer();
    }
}

void Framework::OnCleanUp()
{
    for(auto it = _cleanupSysList.begin();it != _cleanupSysList.end();it++)
    {
        (*it)->CleanUp();
    }
}

}
