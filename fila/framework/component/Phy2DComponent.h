#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <set>
#include "box2d.h"

namespace fl {


class Phy2DComponent : public Component
{
public:
    enum class BodyType
    {
        Static,
        Kinematic,
        Dynamic,
        
        Max
    };

    
public:
    static const char* ClsName() {return "Phy2DComponent";}
    Phy2DComponent();
    
    
    void SetBodyType(BodyType bodyType) { _bodyType = bodyType; }
    
    b2Body* GetBody() { return _body; }
    bool HasBodyCreated() { return GetBody() != nullptr; }
    void CreateBody(b2World* world,const glm::vec3& pos);
    
    
    void DumpResult();
    
    
    
protected:
    void CreateAsDynamic(b2World* world,const glm::vec3& pos);
    void CreateAsStatic(b2World* world,const glm::vec3& pos);
    
protected:
    b2Body*         _body = nullptr;
    BodyType        _bodyType = BodyType::Dynamic;
};
}
