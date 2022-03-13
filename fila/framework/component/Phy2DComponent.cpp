#include "Phy2DComponent.h"
#include "glm.hpp"


static const int kPolygonVertexStride = 2;

namespace fl
{

Phy2DComponent::Phy2DComponent()
{
    
}

void Phy2DComponent::SetPolygonShapePoints(const std::vector<b2Vec2>& points)
{
    _polygonShapePoints = points;
}

void Phy2DComponent::CreateBody(b2World* world,const glm::vec3& pos)
{
    switch(_bodyType)
    {
        case BodyType::Static:
            CreateAsStatic(world,pos);
            break;
        case BodyType::Kinematic:
            break;
        case BodyType::Dynamic:
            CreateAsDynamic(world,pos);
            break;
        default:
            
            break;
    }
    CreateDebugDisplay();
}

void Phy2DComponent::CreateAsDynamic(b2World* world,const glm::vec3& pos)
{
    /*
     enum b2BodyType
     {
         b2_staticBody = 0,
         b2_kinematicBody,
         b2_dynamicBody
     };
     **/
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position.Set(pos.x,pos.y);
    
    _body = world->CreateBody(&def);
    
    
    b2PolygonShape shape;
    shape.SetAsBox(1.0f,1.0f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    
    _fixture = _body->CreateFixture(&fixtureDef);
}

void Phy2DComponent::CreateAsStatic(b2World* world,const glm::vec3& pos)
{
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(pos.x,pos.y);
    
    _body = world->CreateBody(&def);
    
    
    b2PolygonShape shape;
    if(_polygonShapePoints.size() == 0)
    {
        shape.SetAsBox(1.0,1.0);
    }
    else
    {
        shape.Set(&_polygonShapePoints[0],(int)_polygonShapePoints.size());
    }
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    
    _fixture = _body->CreateFixture(&fixtureDef);
}

void Phy2DComponent::DumpResult()
{
    b2Vec2 pos = _body->GetPosition();
    float angle = _body->GetAngle();
    
    printf("pos[%.3f,%.3f] ange:%.3f\n",pos.x,pos.y,angle);
}

void Phy2DComponent::CreateDebugDisplay()
{
    b2Shape* shape = _fixture->GetShape();
    
    switch(shape->GetType())
    {
        case b2Shape::Type::e_polygon:
        {
            BuildDebugVertices();
            BuildDebugVAO();
        }
            
            break;
        default:
            break;
    }
}

void Phy2DComponent::BuildDebugVertices()
{
    // phy data
    b2Shape* shape = _fixture->GetShape();
    b2PolygonShape* polyShape = dynamic_cast<b2PolygonShape*>(shape);
    
    assert(polyShape != nullptr);
    assert(polyShape->m_count > 0);
    
//    printf("------ phy vertices ----- \n");
//    _vertexData.reserve(polyShape->m_count);
    for(int i = 0;i < polyShape->m_count;i++)
    {
        const b2Vec2& vertex = polyShape->m_vertices[i];
        _vertexData.push_back(vertex.x);
        _vertexData.push_back(vertex.y);
        
        if(i - 1 >= 0)
        {
            _indicesData.push_back(i - 1);
        }
        else
        {
            _indicesData.push_back(polyShape->m_count - 1);
        }
        _indicesData.push_back(i);
        
//        printf("[%.3f,%.3f]\t",vertex.x,vertex.y);
    }

//    printf("\n");
}

void Phy2DComponent::BuildDebugVAO()
{
    
    // gl data
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);
    
    glBindVertexArray(_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // vbo data
            unsigned long bufferSize = sizeof(_vertexData[0]) * _vertexData.size();
            void* bufferAddress = &_vertexData[0];
            glBufferData(GL_ARRAY_BUFFER,bufferSize,bufferAddress,GL_STATIC_DRAW);
            
            // attribute pos
            {
                glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,kPolygonVertexStride * sizeof(float),(void*)0);
                glEnableVertexAttribArray(0);
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        
        // ebo data
        const unsigned long bufferSize = sizeof(_indicesData[0]) * _indicesData.size();
        const void* bufferAddress = &_indicesData[0];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,bufferSize,bufferAddress,GL_STATIC_DRAW);
        
        
    }
    glBindVertexArray(0);
}

}
