#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>

namespace fl {

enum class EVertexAttrType
{
    POS,
    POS_UV,
    POS_UV_COLOR,
    POS_UV_COLOR_NORMAL,
    POS_UV_COLOR_NORMAL_TANGENT_BITANGENT,
    
    MAX,
};

class PremitiveComponent : public Component
{
public:
    PremitiveComponent(EVertexAttrType vertAttrType = EVertexAttrType::POS);
    
    void AddVertex(const glm::vec3& pos);
    void SetVertexPos(int vertexIndex,const glm::vec3& pos);
    void SetVertexColor(int vertexIndex,const glm::vec4& color);
    void SetVertexUV(int vertexIndex,const glm::vec2& color);
    void SetVertexNormal(int vertexIndex,const glm::vec3& normal);
    void SetVertexTangent(int vertexIndex,const glm::vec3& tangent);
    void SetVertexBitangent(int vertexIndex,const glm::vec3& bitangent);
    
protected:
    int GetVertexStride() const;
    
protected:
    std::vector<float>      _vertexData;
    EVertexAttrType         _vertAttrType = EVertexAttrType::POS;
};

}
