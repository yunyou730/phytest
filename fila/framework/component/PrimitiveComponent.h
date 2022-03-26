#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

#include "PrimitiveManager.h"

namespace fl {


class PrimObject;
class PrimitiveComponent : public Component
{
public:
    static const char* ClsName() {return "PrimitiveComponent";}
    
    PrimitiveComponent(EPrimitiveType primType);
    
    GLuint GetVAO() const;
    bool IsEBOEnable() const;
    int GetVerticesCount() const;
    int GetIndicesCount() const;
    
protected:
    PrimObject* _primObject = nullptr;
};

}
