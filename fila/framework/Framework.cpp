#include "Framework.h"
#include "system/System.h"
#include "Entity.h"
#include "TransformComponent.h"

#define RegisterSysByType(sys,SysType,Container) ({\
auto item = dynamic_cast<SysType*>(sys);\
if(item != nullptr)\
{\
    Container.push_back(item);\
}\
})\

namespace fl {

Framework::Framework(Application* app)
    :_app(app)
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
    RegisterSysByType(sys,ISysGUISupport,_guiSupportSysList);
    RegisterSysByType(sys,ISysGUI,_guiSysList);
    RegisterSysByType(sys,ISysLateUpdate,_lateUpdateSysList);
}

void Framework::RegisterWorldComponent(const std::string& wcClsName,WorldComponent* comp)
{
    auto it = _worldCompMap.find(wcClsName);
    assert(it == _worldCompMap.end());
    _worldCompMap.insert(std::make_pair(wcClsName,comp));
}

Entity* Framework::CreateEntity()
{
    _entityIdSeed++;
    
    Entity* entity = new Entity(this,_entityIdSeed);
    _entityMap.insert(std::make_pair(_entityIdSeed,entity));
    
    // auto create transform component
    auto transform = new TransformComponent();
    entity->AddComponent(CLASS_NAME(TransformComponent), transform);
    
    return entity;
}

void Framework::DestroyEntity(const int entityID)
{
    auto it = _entityMap.find(entityID);
    if(it != _entityMap.end())
    {
        Entity* entity = it->second;
        SAFE_DEL(entity);
        _entityMap.erase(it);
    }
}

void Framework::OnPrepare(const LaunchParam& launchParam)
{
    for(auto it = _prepareSysList.begin();it != _prepareSysList.end();it++)
    {
        (*it)->Prepare(launchParam);
    }
}

void Framework::OnUpdate()
{
    for(auto it = _updateSysList.begin();it != _updateSysList.end();it++)
    {
        (*it)->Update();
    }
}

void Framework::OnLateUpdate()
{
    for(auto it = _lateUpdateSysList.begin();it != _lateUpdateSysList.end();it++)
    {
        (*it)->LateUpdate();
    }
}

void Framework::OnRender()
{
    // Render
    for(auto it = _renderSysList.begin();it != _renderSysList.end();it++)
    {
        (*it)->Renderer();
    }
    
    // GUI
    for(auto it = _guiSupportSysList.begin();it != _guiSupportSysList.end();it++)
    {
        (*it)->BeforeGUI();
    }
    
    for(auto it = _guiSysList.begin();it != _guiSysList.end();it++)
    {
        (*it)->OnGUI();
    }
    
    for(auto it = _guiSupportSysList.begin();it != _guiSupportSysList.end();it++)
    {
        (*it)->AfterGUI();
    }
}

void Framework::OnCleanUp()
{
    for(auto it = _cleanupSysList.begin();it != _cleanupSysList.end();it++)
    {
        (*it)->CleanUp();
    }
}

unsigned int Framework::NextEntityID()
{
    _entityIdSeed++;
    return _entityIdSeed;
}

std::vector<Entity*> Framework::QueryEntityWithCompSet(std::set<std::string> compSet)
{
    std::vector<Entity*> entities;
    for(auto it = _entityMap.begin();it != _entityMap.end();it++)
    {
        Entity* entity = it->second;
        
//        entity->DumpComponent();
        if(entity->CheckComponent(compSet))
        {
            entities.push_back(entity);
        }
    }
    return entities;
}

Entity* Framework::GetEntity(const int entityID)
{
    auto it = _entityMap.find(entityID);
    if(it != _entityMap.end())
    {
        return it->second;
    }
    return nullptr;
}

}

