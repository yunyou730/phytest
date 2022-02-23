//
//  main.cpp
//  phytest
//
//  Created by bytedance on 2022/2/21.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "box2d.h"

#include "../fila/fila.h"
#include "common.h"

void TestBox2D()
{
    // ground
    b2Vec2 gravity(0.0f,-10.0f);
    b2World world(gravity);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f,-10.0f);
    
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f,10.0f);
    groundBody->CreateFixture(&groundBox,0.0f);
    
    
    // dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    
    body->CreateFixture(&fixtureDef);
    
    
    // simulating the world
    float timeStep = 1.0f / 60.0f;
    
    
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for(int32 i = 0;i < 60;i++)
    {
        world.Step(timeStep,velocityIterations,positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n",position.x,position.y,angle);
    }
    
    // cleanup
}

int main(int argc, const char * argv[])
{
    fl::LaunchParam param;
    param.viewportWidth = 800;
    param.viewportHeight = 600;
    param.clearColorR = 0.2f;
    param.clearColorG = 0.3f;
    param.clearColorB = 0.6f;
    
    fl::Application app;
    fl::Window window("adid",param);
    
    window.Create();
    window.MainLoop(&app,param);
    window.Destroy();
    
    return 0;
}
