#include "PrimitiveComponent.h"
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

PrimitiveComponent::PrimitiveComponent(EVertexAttrType vertAttrType)
    :_vertAttrType(vertAttrType)
{
    
}

void PrimitiveComponent::AddVertex(const glm::vec3& pos)
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

void PrimitiveComponent::AddVertex(const glm::vec3& pos,const glm::vec2& uv)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV);
    AddVertex(pos);
    SetVertexUV(GetVerticesCount() - 1,uv);
}

void PrimitiveComponent::AddVertex(const glm::vec3& pos,const glm::vec2& uv,const glm::vec3& color)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR);
    AddVertex(pos,uv);
    SetVertexColor(GetVerticesCount() - 1,color);
}

void PrimitiveComponent::SetVertexPos(int vertexIndex,const glm::vec3& pos)
{
    int subIndex = GetVertexStride() * vertexIndex;
    _vertexData[subIndex++] = pos.x;
    _vertexData[subIndex++] = pos.y;
    _vertexData[subIndex++] = pos.z;
}


void PrimitiveComponent::SetVertexUV(int vertexIndex,const glm::vec2& uv)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize;
    _vertexData[subIndex++] = uv.x;
    _vertexData[subIndex++] = uv.y;
}

void PrimitiveComponent::SetVertexColor(int vertexIndex,const glm::vec3& color)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize;
    _vertexData[subIndex++] = color.r;
    _vertexData[subIndex++] = color.g;
    _vertexData[subIndex++] = color.b;
}

void PrimitiveComponent::SetVertexNormal(int vertexIndex,const glm::vec3& normal)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize;
    _vertexData[subIndex++] = normal.x;
    _vertexData[subIndex++] = normal.y;
    _vertexData[subIndex++] = normal.z;
}

void PrimitiveComponent::SetVertexTangent(int vertexIndex,const glm::vec3& tangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize;
    _vertexData[subIndex++] = tangent.x;
    _vertexData[subIndex++] = tangent.y;
    _vertexData[subIndex++] = tangent.z;
}

void PrimitiveComponent::SetVertexBitangent(int vertexIndex,const glm::vec3& bitangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize + kTangentSize;
    _vertexData[subIndex++] = bitangent.x;
    _vertexData[subIndex++] = bitangent.y;
    _vertexData[subIndex++] = bitangent.z;
}

int PrimitiveComponent::GetVertexStride() const
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

void PrimitiveComponent::Commit()
{
    assert(_vertexData.size() > 0);
    
    unsigned int stride = GetVertexStride();
    
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
            glBufferData(GL_ARRAY_BUFFER,sizeof(_vertexData[0]) * _vertexData.size(),&_vertexData[0],GL_STATIC_DRAW);
            
            // specy how to explain data format
            switch(_vertAttrType)
            {
                case EVertexAttrType::POS:
                {

                    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)0);
                    glEnableVertexAttribArray(0);
                }
                    break;
                case EVertexAttrType::POS_UV:
                {
                    // slot 0,pos
                    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride* sizeof(float),(void*)0);
                    glEnableVertexAttribArray(0);
                    // slot 1, uv
                    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(sizeof(GL_FLOAT) * 3));
                    glEnableVertexAttribArray(1);
                }
                    break;
                case EVertexAttrType::POS_UV_COLOR:
                {
                    // slot 0,pos
                    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride* sizeof(float),(void*)0);
                    glEnableVertexAttribArray(0);
                    // slot 1, uv
                    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(sizeof(GL_FLOAT) * 3));
                    glEnableVertexAttribArray(1);
                    // slot 2, color
                    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(sizeof(GL_FLOAT) * 5));
                    glEnableVertexAttribArray(2);
                }
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
    }
    glBindVertexArray(0);
}

GLuint PrimitiveComponent::GetVAO() const
{
    
    return _vao;
}

int PrimitiveComponent::GetVerticesCount() const
{
    return _vertexData.size() / GetVertexStride();
}

}

