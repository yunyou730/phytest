#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace fl {

class TransformComponent : public Component
{
public:
    TransformComponent();

    void SetPosition(const glm::vec3& pos);
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    glm::vec3 GetPos() const { return _pos;}
    
    void SetScaleX(float sx);
    void SetScaleY(float sy);
    void SetScaleZ(float sz);
    void SetScale(const glm::vec3& scale);
    
    void SetRotation(float rotByX,float rotByY,float rotByZ);
    void SetRotationX(float degree);
    void SetRotationY(float degree);
    void SetRotationZ(float degree);
    
    const glm::mat4& GetModelMatrix();
    
protected:
    void CalcModelMatrix();
    
protected:
    glm::vec3   _scale;
    glm::vec3   _rotByEachAxis; // in degree
    glm::vec3   _pos;
    
    bool    _bDirty = true;
    
    glm::mat4  _modelMatrix;
};

}
