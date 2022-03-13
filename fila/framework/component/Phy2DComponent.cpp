#include "Phy2DComponent.h"
#include "glm.hpp"


static const int kPolygonVertexStride = 2;

namespace fl
{

Phy2DComponent::Phy2DComponent()
{
    
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
    /*
     enum b2BodyType
     {
         b2_staticBody = 0,
         b2_kinematicBody,
         b2_dynamicBody
     };
     **/
    b2BodyDef def;
    def.type = b2_staticBody;
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
            // phy data
            b2PolygonShape* polyShape = dynamic_cast<b2PolygonShape*>(shape);
            
            _vertexData.reserve(polyShape->m_count);
            for(int i = 0;i < polyShape->m_count;i++)
            {
                _vertexData.push_back(polyShape->m_vertices[i].x);
                _vertexData.push_back(polyShape->m_vertices[i].y);
                _indicesData.push_back(i);
            }
            
            
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
            
            break;
        default:
            break;
    }
}

}
