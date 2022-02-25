#pragma once
#include <map>
#include <set>
#include <string>

#include "PremitiveComponent.h"

namespace fl {

class Component;
class Entity
{
public:
    Entity(unsigned int entityId);
    ~Entity();
    unsigned int GetID() const { return _entityId; }
    
    bool HasComponent(const std::string& compClsName);
    void AddComponent(const std::string& compClsName,Component* component);
    bool CheckComponent(const std::set<std::string>& compClsSet);
    void DumpComponent() const;
    
    template<typename CompCls>
    CompCls* GetComponent(const std::string& compClsName)
    {
        auto it = _componentMap.find(compClsName);
        if(it != _componentMap.end())
        {
            Component* comp = it->second;
            CompCls* p = dynamic_cast<CompCls*>(comp);
            return p;
        }
        return nullptr;
    }
    
protected:
    unsigned int _entityId = 0;
    std::map<std::string,Component*> _componentMap;
};

}
