#pragma once
#include "application.h"
#include "glm.hpp"

namespace fl
{
class Window;
}

namespace ad {

class Game : public fl::Application
{
public:
    Game();
    virtual ~Game();
    
    virtual void OnPrepare(fl::Window* window,const fl::LaunchParam& launchParam);
    virtual void OnCleanup();
    
    virtual void OnUpdate();
    virtual void OnRenderer();
    
protected:
    void CreatePersCamera(int viewportWidth,int viewportHeight);
    void CreateOthoCamera(int viewportWidth,int viewportHeight);
    
    void CreateVBOTest();
    void CreateEBOTest();
    void CreateBox();

    void CreatePhyBox(const glm::vec3& pos);
    void CreatePhyGround(const glm::vec3& pos);
};

}

