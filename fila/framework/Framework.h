#pragma once
#include <vector>
#include <map>
#include <string>
#include "WorldComponent.h"
#include "System.h"

namespace fl {

class Framework
{
public:
    Framework();
    virtual ~Framework();
    
public:
    void OnPrepare(const PrepareParam& prepareParam);
    void OnUpdate();
    void OnRender();
    void OnCleanUp();
    
public:
    void RegisterSystem(System* sys);
    void RegisterWorldComponent(const std::string& wcClsName,WorldComponent* comp);
    
    template<typename WCType>
    WCType* GetWorldComponent(const std::string& wcClsName)
    {
        auto it = _worldCompMap.find(wcClsName);
        if(it != _worldCompMap.end())
        {
            return dynamic_cast<WCType*>(it->second);
        }
        return nullptr;
    }
    
    
protected:
    std::vector<ISysPrepare*>       _prepareSysList;
    std::vector<ISysUpdate*>        _updateSysList;
    std::vector<ISysRenderer*>      _renderSysList;
    std::vector<ISysCleanup*>       _cleanupSysList;
    
    std::map<std::string,WorldComponent*>    _worldCompMap;
    
};

}
