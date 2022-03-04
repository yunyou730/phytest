#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../utils/common.h"

namespace fl
{
class Application;
class Window
{
public:
    Window(const std::string& name,const fl::LaunchParam& launchParam);
    virtual ~Window();
    
public:
    bool Create();
    void MainLoop(Application* app,const fl::LaunchParam& launchParam);
    void Destroy();
    
protected:
    static void InitEnv();
    
    float ProcessFPS(int desireFPS);
    
protected:
    std::string _name   = "fila";
    GLFWwindow* _window = nullptr;
    int _width = 800;
    int _height = 600;
    
    float _fpsTimeCounter = 0.0f;
};



}
