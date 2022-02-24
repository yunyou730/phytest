#pragma once
#include <map>
#include <set>
#include <string>

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
    
protected:
    unsigned int _entityId = 0;
    
    
};

}
