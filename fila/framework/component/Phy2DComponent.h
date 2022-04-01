#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <set>
#include "box2d.h"

#include <vector>
#include <glad/glad.h>

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
    virtual ~Phy2DComponent();
    
    void SetBodyType(BodyType bodyType) { _bodyType = bodyType; }
    void SetPolygonShapePoints(const std::vector<b2Vec2>& points);
    
    
    b2Body* GetBody() { return _body; }
    bool HasBodyCreated() { return GetBody() != nullptr; }
    void CreateBody(b2World* world,const glm::vec3& pos);
    
    void DumpResult();
    
protected:
    void CreateAsDynamic(b2World* world,const glm::vec3& pos);
    void CreateAsStatic(b2World* world,const glm::vec3& pos);
    
    void CreateDebugDisplay();
    void BuildDebugVertices();
    void BuildDebugVAO();
    
    
public:
    b2Body*         _body = nullptr;
    b2Fixture*      _fixture = nullptr;
    BodyType        _bodyType = BodyType::Dynamic;
    std::vector<b2Vec2>     _polygonShapePoints;
    
public:
    // display debug
    std::vector<float>      _vertexData;
    std::vector<int>        _indicesData;
    
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
};
}
