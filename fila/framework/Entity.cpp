#include "Entity.h"

namespace fl {

Entity::Entity(unsigned int entityId)
    :_entityId(entityId)
{
    
}

Entity::~Entity()
{
    
}

bool Entity::HasComponent(const std::string& compClsName)
{
    return false;
}

void Entity::AddComponent(const std::string& compClsName,Component* component)
{
    
}

bool Entity::CheckComponent(const std::set<std::string>& compClsSet)
{
    return false;
}

}
