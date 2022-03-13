#include "Phy2DComponent.h"
#include "glm.hpp"

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
    void CreateAsDynamic();
    void CreateAsStatic();

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
    
    _body->CreateFixture(&fixtureDef);
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
    
    _body->CreateFixture(&fixtureDef);
}

void Phy2DComponent::DumpResult()
{
    b2Vec2 pos = _body->GetPosition();
    float angle = _body->GetAngle();
    
    printf("pos[%.3f,%.3f] ange:%.3f\n",pos.x,pos.y,angle);
}

}
