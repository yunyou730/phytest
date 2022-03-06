#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

namespace fl {

enum class ERenderPrimitiveType
{
    Triangle,
    Point,
    
    Max,
};

enum class ERenderFillMode
{
    Fill,
    Wireframe,
    
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
    static const char* ClsName() {return "RenderStateComponent";}
    
    void SetShaderId(unsigned int shaderId) { _shaderId = shaderId; }
    unsigned int GetShaderId() const { return _shaderId; }
        
    void SetPrimitiveType(ERenderPrimitiveType primitiveType) {_primitiveType = primitiveType;}
    ERenderPrimitiveType GetPrimitiveType() const { return _primitiveType;}
    
    void SetFillMode(ERenderFillMode fillMode) { _fillMode = fillMode; }
    ERenderFillMode GetFillMode() const { return _fillMode;}
    
    void SetPointSize(float pointSize) { _pointSize = pointSize;}
    float GetPointSize() const { return _pointSize;}
    
    void SetRenderLayer(int layerIndex) { _renderLayerInex = layerIndex; }
    int GetRenderLayer() const { return _renderLayerInex;}
    
protected:
    unsigned int _shaderId = 0;
    ERenderPrimitiveType  _primitiveType = ERenderPrimitiveType::Triangle;
    ERenderFillMode     _fillMode = ERenderFillMode::Fill;
    float _pointSize = 20.0f;
    
    int _renderLayerInex = 1;
};

}
