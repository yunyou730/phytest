#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

namespace fl {

/*
从上到下，依次序是被嵌套 与 嵌套的关系
*/
enum class EVertexAttrType
{
    POS,
    POS_UV,
    POS_UV_COLOR,
    POS_UV_COLOR_NORMAL,        // temp not suport
    POS_UV_COLOR_NORMAL_TANGENT_BITANGENT,  // temp not suport
    
    MAX,
};

class PrimitiveComponent : public Component
{
public:
    static const char* ClsName() {return "PrimitiveComponent";}
    PrimitiveComponent(EVertexAttrType vertAttrType,bool bEnableEBO);
    
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
    int GetIndicesCount() const;
    
    void SetIndexData(const std::vector<int>& indexData);
    bool IsEBOEnable() const { return _bEnableEBO;}
    
protected:
    void CommitVBO(int stride);
    void CommitEBO();
    
protected:
    int GetVertexStride() const;
    
protected:
    std::vector<float>      _vertexData;
    EVertexAttrType         _vertAttrType = EVertexAttrType::POS;
    
    // vao,vbo,ebo
    GLuint _vao = 0;
    GLuint _vbo = 0;
    GLuint _ebo = 0;
    
    bool                _bEnableEBO = false;
    std::vector<int>    _indexData;
};

}
