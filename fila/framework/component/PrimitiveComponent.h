#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

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

class PrimitiveComponent : public Component
{
public:
    PrimitiveComponent(EVertexAttrType vertAttrType = EVertexAttrType::POS);
    
    void AddVertex(const glm::vec3& pos);
    void AddVertex(const glm::vec3& pos,const glm::vec2& uv);
    void AddVertex(const glm::vec3& pos,const glm::vec2& uv,const glm::vec3& color);
    
    void SetVertexPos(int vertexIndex,const glm::vec3& pos);
    void SetVertexColor(int vertexIndex,const glm::vec3& color);
    void SetVertexUV(int vertexIndex,const glm::vec2& uv);
    void SetVertexNormal(int vertexIndex,const glm::vec3& normal);
    void SetVertexTangent(int vertexIndex,const glm::vec3& tangent);
    void SetVertexBitangent(int vertexIndex,const glm::vec3& bitangent);
    
    void Commit();
    GLuint GetVAO() const;
    
    int GetVerticesCount() const;
    
protected:
    int GetVertexStride() const;
    
protected:
    std::vector<float>      _vertexData;
    EVertexAttrType         _vertAttrType = EVertexAttrType::POS;
    
    // vao,vbo,ebo
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
};

}
