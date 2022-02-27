#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace fl {

TransformComponent::TransformComponent()
{
    
}

void TransformComponent::SetPosition(const glm::vec3& pos)
{
    _pos = pos;
    _bDirty = true;
}

void TransformComponent::SetX(float x)
{
    _pos.x = x;
    _bDirty = true;
}

void TransformComponent::SetY(float y)
{
    _pos.y = y;
    _bDirty = true;
}

void TransformComponent::SetZ(float z)
{
    _pos.z = z;
    _bDirty = true;
}

void TransformComponent::SetScaleX(float sx)
{
    _scale.x = sx;
    _bDirty = true;
}

void TransformComponent::SetScaleY(float sy)
{
    _scale.y = sy;
    _bDirty = true;
}

void TransformComponent::SetScaleZ(float sz)
{
    _scale.z = sz;
    _bDirty = true;
}

void TransformComponent::SetScale(const glm::vec3& scale)
{
    _scale = scale;
    _bDirty = true;
}

void TransformComponent::SetRotation(float rotByX,float rotByY,float rotByZ)
{
    _rotByEachAxis = glm::vec3(rotByX,rotByY,rotByZ);
    _bDirty = true;
}

void TransformComponent::SetRotationX(float degree)
{
    _rotByEachAxis.x = degree;
    _bDirty = true;
}

void TransformComponent::SetRotationY(float degree)
{
    _rotByEachAxis.y = degree;
    _bDirty = true;
}

void TransformComponent::SetRotationZ(float degree)
{
    _rotByEachAxis.z = degree;
    _bDirty = true;
}

const glm::mat4& TransformComponent::GetModelMatrix()
{
    if(_bDirty)
    {
        CalcModelMatrix();
        _bDirty = false;
    }
    return _modelMatrix;
}

void TransformComponent::CalcModelMatrix()
{
    // scale part
    glm::mat4 scale(1.0);
    scale = glm::scale(scale,_scale);
    
    // rotation part
    glm::mat4 rotByX(1.0),rotByY(1.0),rotByZ(1.0);
    
    rotByX = glm::rotate(rotByX,glm::radians(_rotByEachAxis.x) , glm::vec3(1.0f, 0.0f, 0.0f));
    rotByY = glm::rotate(rotByX,glm::radians(_rotByEachAxis.y) , glm::vec3(0.0f, 1.0f, 0.0f));
    rotByZ = glm::rotate(rotByX,glm::radians(_rotByEachAxis.z) , glm::vec3(0.0f, 0.0f, 1.0f));
    
    glm::mat4 rot = rotByX * rotByY * rotByZ;
    
    
    // translate part
    glm::mat4 translate(1.0);
    translate = glm::translate(translate,_pos);
    
    
    _modelMatrix = scale * rot * translate;
    
}

}
