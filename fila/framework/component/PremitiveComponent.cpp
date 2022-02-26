#include "PremitiveComponent.h"
#include <cassert>

namespace fl
{

/*
    _vertexData format
    pos x3, uv x2,color x3,normal x3,tangent x3,bitangent x3
 */
static const int kPosSize       = 3;
static const int kUVSize        = 2;
static const int kColorSize     = 3;
static const int kNormalSize    = 3;
static const int kTangentSize   = 3;
static const int kBitangentSize = 3;

PremitiveComponent::PremitiveComponent(EVertexAttrType vertAttrType)
    :_vertAttrType(vertAttrType)
{
    
}

void PremitiveComponent::AddVertex(const glm::vec3& pos)
{
    _vertexData.push_back(pos.x);
    _vertexData.push_back(pos.y);
    _vertexData.push_back(pos.z);
    
    int stride = GetVertexStride();
    int needFill = stride - kPosSize;
    for(int i = 0;i < needFill;i++)
    {
        _vertexData.push_back(0.0);
    }
}

void PremitiveComponent::SetVertexPos(int vertexIndex,const glm::vec3& pos)
{
    int subIndex = GetVertexStride() * vertexIndex;
    _vertexData[subIndex++] = pos.x;
    _vertexData[subIndex++] = pos.y;
    _vertexData[subIndex++] = pos.z;
}


void PremitiveComponent::SetVertexUV(int vertexIndex,const glm::vec2& uv)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize;
    _vertexData[subIndex++] = uv.x;
    _vertexData[subIndex++] = uv.y;
}

void PremitiveComponent::SetVertexColor(int vertexIndex,const glm::vec4& color)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize;
    _vertexData[subIndex++] = color.r;
    _vertexData[subIndex++] = color.g;
    _vertexData[subIndex++] = color.b;
}

void PremitiveComponent::SetVertexNormal(int vertexIndex,const glm::vec3& normal)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize;
    _vertexData[subIndex++] = normal.x;
    _vertexData[subIndex++] = normal.y;
    _vertexData[subIndex++] = normal.z;
}

void PremitiveComponent::SetVertexTangent(int vertexIndex,const glm::vec3& tangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize;
    _vertexData[subIndex++] = tangent.x;
    _vertexData[subIndex++] = tangent.y;
    _vertexData[subIndex++] = tangent.z;
}

void PremitiveComponent::SetVertexBitangent(int vertexIndex,const glm::vec3& bitangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize + kTangentSize;
    _vertexData[subIndex++] = bitangent.x;
    _vertexData[subIndex++] = bitangent.y;
    _vertexData[subIndex++] = bitangent.z;
}

int PremitiveComponent::GetVertexStride() const
{
    switch(_vertAttrType)
    {
        case EVertexAttrType::POS:
            return kPosSize;
        case EVertexAttrType::POS_UV:
            return kPosSize + kUVSize;
        case EVertexAttrType::POS_UV_COLOR:
            return kPosSize + kUVSize + kColorSize;
        case EVertexAttrType::POS_UV_COLOR_NORMAL:
            return kPosSize + kUVSize + kColorSize + kNormalSize;
        case EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT:
            return kPosSize + kUVSize + kColorSize + kNormalSize + kTangentSize + kBitangentSize;
        default:
            break;
    }
    return 0;
}

void PremitiveComponent::Commit()
{
    assert(_vertexData.size() > 0);
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    
    glBindVertexArray(_vao);
    {
        /*
         POS,
         POS_UV,
         POS_UV_COLOR,
         POS_UV_COLOR_NORMAL,
         POS_UV_COLOR_NORMAL_TANGENT_BITANGENT,
         **/
        
        glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        {
            // pass data to vbo
            glBufferData(GL_ARRAY_BUFFER,sizeof(_vertexData[0]) * _vertexData.size(),&(_vertexData[0]),GL_STATIC_DRAW);
            
            // specy how to explain data format
            switch(_vertAttrType)
            {
                case EVertexAttrType::POS:
                {
                    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
                    glEnableVertexAttribArray(0);
                }
                    break;
                default:
                    break;
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
    }
    glBindVertexArray(0);
}

GLuint PremitiveComponent::GetVAO() const
{
    
    return _vao;
}

int PremitiveComponent::GetVerticesCount() const
{
    return _vertexData.size() / GetVertexStride();
}

}

