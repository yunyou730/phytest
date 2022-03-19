#pragma once
#include "application.h"
#include "glm.hpp"

namespace fl
{
class Window;
class Entity;
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
    void CreateOrthoCamera(int viewportWidth,int viewportHeight);
    
    void CreateVBOTest();
    void CreateEBOTest();
    void CreateBox();

    void CreatePhyBox(const glm::vec3& pos);
    fl::Entity* CreatePhyGround(const glm::vec3& pos);
    fl::Entity* CreatePhyGround(const glm::vec3& pos,const std::vector<b2Vec2>& polygonPoints);
};

}

