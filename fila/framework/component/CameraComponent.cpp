#include "CameraComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>

namespace fl {

CameraComponent::CameraComponent(float viewportWidth,float viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
{
    _renderLayers.insert(1);
    _lookDir = glm::vec3(0,0,1);
    _upDir = glm::vec3(0,1,0);
}

bool CameraComponent::CheckLayer(int layer)
{
    return _renderLayers.find(layer) != _renderLayers.end();
}

void CameraComponent::SetLookDir(const glm::vec3& lookDir)
{
    _lookDir = glm::normalize(lookDir);
    
    // @miao @todo
    // 这里可能需要重新计算 up, right ，
    // 也可能不需要， glm::lookAt 可能里面给封装好了
    // todo
}

glm::mat4& CameraComponent::GetViewMatrix(const glm::vec3& cameraPos)
{
    glm::vec3 center = cameraPos + _lookDir;
    _viewMatrix = glm::lookAt(cameraPos,center, _upDir);
    
    return _viewMatrix;
}

glm::mat4& CameraComponent::GetProjectionMatrix()
{
//    _projectionMatrix = glm::identity<glm::mat4>();
    // @miao @todo
    
    float aspect = _viewportWidth / _viewportHeight;
    _projectionMatrix = glm::perspective(glm::radians(_fovY), aspect, _zNear, _zFar);
    
    return _projectionMatrix;
}

glm::vec3 CameraComponent::LookDir() const
{
    return _lookDir;
}

glm::vec3 CameraComponent::UpDir() const
{
    return _upDir;
}

glm::vec3 CameraComponent::RightDir() const
{
    glm::vec3 right = -glm::cross(_lookDir,_upDir);
    return glm::normalize(right);
}

}
