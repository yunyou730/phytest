#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common.h"

namespace fl
{
class Application;
class Window
{
public:
    Window(const std::string& name,int width,int height);
    virtual ~Window();
    
public:
    bool Create();
    void MainLoop(Application* app,const PrepareParam& prepareParam);
    void Destroy();
    
protected:
    static void InitEnv();
    
protected:
    std::string _name   = "fila";
    GLFWwindow* _window = nullptr;
    int _width = 800;
    int _height = 600;
};



}
