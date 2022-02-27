#pragma once

namespace fl {

class Entity;
class Component
{
public:
    virtual ~Component() {}
    
    void SetEntity(Entity* entity) { _entity = entity; }
    Entity* GetEntity() { return _entity;}
    
protected:
    Entity* _entity = nullptr;
    
};

}

