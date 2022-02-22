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

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
 glViewport(0,0,width,height);
 printf("%d,%d\n",width,height);
}

void processInput(GLFWwindow *window)
{
 if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  glfwSetWindowShouldClose(window, true);
}

int main(int argc, const char * argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   
   
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
   
   
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
   std::cout << "Failed to initialize GLAD" << std::endl;
   return -1;
  }
   

  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
   
  glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
  while(!glfwWindowShouldClose(window))
  {
    processInput(window);

    // Render code here
    glClear(GL_COLOR_BUFFER_BIT); // render begin

    // render end
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
