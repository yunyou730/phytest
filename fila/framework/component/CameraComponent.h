#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <set>

namespace fl {

enum class ECameraType
{
    Perspective,
    Ortho,
    
    Max,
};

class CameraComponent : public Component
{
public:
    CameraComponent(float viewportWidth,float viewportHeight);
    
    inline void SetZNearFar(float zNear,float zFar) { _zNear = zNear;_zFar = zFar;}
    inline void SetFovY(float fovy) {_fovY = fovy;}
    inline void SetViewportSize(float width,float height) {_viewportWidth = width;_viewportHeight = height;}
    
    int GetSortIndex() const { return _sort; }
    bool CheckLayer(int layer);
    
    void SetLookDir(const glm::vec3& lookDir);
    
protected:
    
    ECameraType _cameraType = ECameraType::Perspective;
    
    float _viewportWidth = 800.0f;
    float _viewportHeight = 600.0f;
    
    float _zNear = 0.1f;
    float _zFar = 100.0f;
    
    float _fovY = 60.0f;
    
    glm::vec3 _lookDir;
    
    
    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    
    int _sort = 1;
    std::set<int> _renderLayers;
};

}