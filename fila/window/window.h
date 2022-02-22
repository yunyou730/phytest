#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace fl
{
class Window
{
public:
    Window(const std::string& name,int width = 800,int height = 600);
    virtual ~Window();
    
public:
    bool Create();
    void MainLoop();
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
