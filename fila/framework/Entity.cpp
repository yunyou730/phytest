#include "Entity.h"
#include "log.h"

namespace fl {

Entity::Entity(Framework* framework,unsigned int entityId)
    :_framework(framework)
    ,_entityId(entityId)
{
    
}

Entity::~Entity()
{
    for(auto it : _componentMap)
    {
        delete it.second;
    }
    _componentMap.clear();
}

bool Entity::HasComponent(const std::string& compClsName)
{
    return _componentMap.find(compClsName) != _componentMap.end();;
}

void Entity::AddComponent(const std::string& compClsName,Component* component)
{
    auto it = _componentMap.find(compClsName);
    assert(it == _componentMap.end());
    component->SetEntity(this);
    _componentMap.insert(std::make_pair(compClsName,component));
}

bool Entity::CheckComponent(const std::set<std::string>& compClsSet)
{
    bool bCheckOK = true;
    for(auto it = compClsSet.begin();it != compClsSet.end();it++)
    {
        if(!HasComponent(*it))
        {
            bCheckOK = false;
            break;
        }
        
    }
    return bCheckOK;
}

void Entity::DumpComponent() const
{
    printf("-----entity id [%d] \n",GetID());
    for(auto it = _componentMap.begin();it != _componentMap.end();it++)
    {
        printf("%s\n",it->first.c_str());
    }
    printf("------\n");
}

}
