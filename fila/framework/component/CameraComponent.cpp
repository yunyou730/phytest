#include "CameraComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>

namespace fl {

CameraComponent::CameraComponent(float viewportWidth,float viewportHeight)
    :_viewportWidth(viewportWidth)
    ,_viewportHeight(viewportHeight)
    ,_lookDir(glm::vec3(0,0,1))
    ,_upDir(glm::vec3(0,1,0))
{
    _renderLayers.insert(1);
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
    float aspect = _viewportWidth / _viewportHeight;
    switch(_cameraType)
    {
        case ECameraType::Perspective:
            _projectionMatrix = glm::perspective(glm::radians(_fovY), aspect, _zNear, _zFar);
            break;
        case ECameraType::Ortho:
            
        {
            float widthField = (_orthoHalf + _orthoHalf) * aspect;
            _projectionMatrix = glm::ortho<float>(-widthField * 0.5,widthField * 0.5,-_orthoHalf,_orthoHalf,_zNear,_zFar);  // fix height,adapth width
            //            _projectionMatrix = glm::ortho<float>(-1,1,-1/aspect,1/aspect,_zNear,_zFar); // fix width,adapth height
        }

            break;
        default:
            break;
    }
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
    
//    glm::vec3 right = glm::cross(_lookDir,_upDir);
  //  return glm::normalize(right);
}

}
