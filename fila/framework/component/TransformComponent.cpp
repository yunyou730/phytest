#include "TransformComponent.h"

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
    // @todo
    
}

}
