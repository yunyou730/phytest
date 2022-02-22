#include "window.h"
#include "application.h"

namespace fl
{

extern void framebufferSizeCallback(GLFWwindow* window,int width,int height);
extern void processInput(GLFWwindow *window);

Window::Window(const std::string& name,int width,int height)
    :_name(name)
    ,_width(width)
    ,_height(height)
{
    InitEnv();
}

Window::~Window()
{
    
}


void Window::InitEnv()
{
    static bool bHasInited = false;
    if(!bHasInited)
    {
        bHasInited = true;
        
        // do init env
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    }
}

bool Window::Create()
{
    _window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    glfwSetFramebufferSizeCallback(_window,framebufferSizeCallback);
    
    return true;
}

void Window::MainLoop(Application* app)
{
    glViewport(0,0,_width,_height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    app->OnPrepare();
    
    while(!glfwWindowShouldClose(_window))
    {
        processInput(_window);
        
        app->OnUpdate();
        
        // Render code here
        glClear(GL_COLOR_BUFFER_BIT); // render begin
        app->OnRenderer();

        // render end
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    
    app->OnCleanup();
}

void Window::Destroy()
{
    glfwTerminate();
}


void framebufferSizeCallback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
    printf("%d,%d\n",width,height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

}
