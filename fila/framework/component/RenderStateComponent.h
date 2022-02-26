#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

namespace fl {

enum class ERenderPrimitiveType
{
    Triangle,
    TriangleFramewire,
    
    Max,
};

/*
    Save render state parameters
    Shader id,
    Primitive type,
    Cull
    Z write
    and so on...
 */
class RenderStateComponent : public Component
{
public:
    void SetShaderId(unsigned int shaderId) { _shaderId = shaderId; }
    unsigned int GetShaderId() const { return _shaderId; }
        
    void SetPrimitiveType(ERenderPrimitiveType primitiveType) {_primitiveType = primitiveType;}
    GLuint GetPrimitiveType() const;
    
protected:
    unsigned int _shaderId = 0;
    ERenderPrimitiveType  _primitiveType = ERenderPrimitiveType::Triangle;
};

}
