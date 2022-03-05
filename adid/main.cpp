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

#include "Game.h"

#include "log.h"

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


glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

void TestMath()
{
    glm::mat4 mat(1.0);
    fl::Log::Info(mat);
    
    mat = glm::rotate(mat,glm::radians<float>(90),glm::vec3(1,0,0));
    fl::Log::Info(mat);
    
    float rad = glm::radians<float>(180);
    float deg = glm::degrees<float>(glm::pi<float>());
    printf("%.3f,%.3f\n",rad,deg);
    
//    glm::mat4 camMat = camera();
    
    
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    fl::Log::Info(Projection);
    
}

int main(int argc, const char * argv[])
{
    TestMath();
    
    fl::LaunchParam param;
    fl::Window window("adid",param);
    ad::Game game;
    
    window.Create();
    window.MainLoop(&game,param);
    window.Destroy();
    
    return 0;
}
