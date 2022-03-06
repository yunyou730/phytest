#include "window.h"
#include "application.h"
#include <thread>

namespace fl
{

extern void framebufferSizeCallback(GLFWwindow* window,int width,int height);
//extern void processInput(GLFWwindow *window);

Window::Window(const std::string& name,const LaunchParam& launchParam)
    :_name(name)
    ,_width(launchParam.viewportWidth)
    ,_height(launchParam.viewportHeight)
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

void Window::MainLoop(Application* app,const LaunchParam& launchParam)
{
    app->OnPrepare(this,launchParam);
    app->SetDesireFPS(60);
    
    _fpsTimeCounter = glfwGetTime();
    
    
    while(!app->ShallExit() || !glfwWindowShouldClose(_window))
    {
        float deltaTime = ProcessFPS(app->GetDesireFPS());
        app->SetDeltaTime(deltaTime);
        
        app->ProcessInput(this);
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

float Window::ProcessFPS(int desireFPS)
{
    float atLeastFrameTime = 1.0f / desireFPS;
    
    double now = glfwGetTime();
    double deltaTime = now - _fpsTimeCounter;
    if(deltaTime < atLeastFrameTime)
    {
        int toSleepMS = int((atLeastFrameTime - deltaTime) * 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(toSleepMS));
    }
    now = glfwGetTime();
    deltaTime = now - _fpsTimeCounter;
    
    _fpsTimeCounter = glfwGetTime();
    return deltaTime;
}


void framebufferSizeCallback(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
    printf("%d,%d\n",width,height);
}

//void processInput(GLFWwindow *window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}

}
