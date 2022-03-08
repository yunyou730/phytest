#pragma once
#include <vector>
#include <map>
#include <string>
#include <set>
#include "WorldComponent.h"
#include "System.h"

namespace fl {

class Application;
class Entity;
class Framework
{
public:
    Framework(Application* app);
    virtual ~Framework();
    
    
public:
    Application* GetApp() const { return _app;}
    
public:
    void OnPrepare(const LaunchParam& launchParam);
    void OnUpdate();
    void OnRender();
    void OnCleanUp();
    void OnGUI();
    
public:
    void RegisterSystem(System* sys);
    void RegisterWorldComponent(const std::string& wcClsName,WorldComponent* comp);
        
    
    template<typename WCType>
    WCType* GetWorldComponent()
    {
        return GetWorldComponent<WCType>(WCType::ClsName());
    }
        
public:
    Entity* CreateEntity();
    std::vector<Entity*> QueryEntityWithCompSet(std::set<std::string> compSet);
    Entity* GetEntity(const int entityID);
    
    const std::map<unsigned int,Entity*>& GetEntityMap() { return _entityMap;}
        
protected:
    unsigned int NextEntityID();
    
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
    std::vector<ISysGUISupport*>    _guiSupportSysList;
    std::vector<ISysGUI*>           _guiSysList;
    
protected:
    std::map<std::string,WorldComponent*>    _worldCompMap;
    
protected:
    std::map<unsigned int,Entity*>  _entityMap;
    unsigned int                    _entityIdSeed = 0;
    
protected:
    Application*    _app = nullptr;
};

}
