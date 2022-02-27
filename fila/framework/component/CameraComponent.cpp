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
}

bool CameraComponent::CheckLayer(int layer)
{
    return _renderLayers.find(layer) != _renderLayers.end();
}

void CameraComponent::SetLookDir(const glm::vec3& lookDir)
{
    _lookDir = lookDir;
    _lookDir = glm::normalize(_lookDir);
}

}
