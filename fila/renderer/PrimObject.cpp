#include "PrimObject.h"

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

PrimObject::PrimObject(EVertexAttrType vertAttrType,bool bEnableEBO)
    :_vertAttrType(vertAttrType)
    ,_bEnableEBO(bEnableEBO)
{
    
}

void PrimObject::AddVertex(const glm::vec3& pos)
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

void PrimObject::AddVertex(const glm::vec3& pos,const glm::vec2& uv)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV);
    AddVertex(pos);
    SetVertexUV(GetVerticesCount() - 1,uv);
}

void PrimObject::AddVertex(const glm::vec3& pos,const glm::vec2& uv,const glm::vec3& color)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR);
    AddVertex(pos,uv);
    SetVertexColor(GetVerticesCount() - 1,color);
}

void PrimObject::SetVertexPos(int vertexIndex,const glm::vec3& pos)
{
    int subIndex = GetVertexStride() * vertexIndex;
    _vertexData[subIndex++] = pos.x;
    _vertexData[subIndex++] = pos.y;
    _vertexData[subIndex++] = pos.z;
}


void PrimObject::SetVertexUV(int vertexIndex,const glm::vec2& uv)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize;
    _vertexData[subIndex++] = uv.x;
    _vertexData[subIndex++] = uv.y;
}

void PrimObject::SetVertexColor(int vertexIndex,const glm::vec3& color)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize;
    _vertexData[subIndex++] = color.r;
    _vertexData[subIndex++] = color.g;
    _vertexData[subIndex++] = color.b;
}

void PrimObject::SetVertexNormal(int vertexIndex,const glm::vec3& normal)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize;
    _vertexData[subIndex++] = normal.x;
    _vertexData[subIndex++] = normal.y;
    _vertexData[subIndex++] = normal.z;
}

void PrimObject::SetVertexTangent(int vertexIndex,const glm::vec3& tangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize;
    _vertexData[subIndex++] = tangent.x;
    _vertexData[subIndex++] = tangent.y;
    _vertexData[subIndex++] = tangent.z;
}

void PrimObject::SetVertexBitangent(int vertexIndex,const glm::vec3& bitangent)
{
    assert(_vertAttrType >= EVertexAttrType::POS_UV_COLOR_NORMAL_TANGENT_BITANGENT);
    int subIndex = GetVertexStride() * vertexIndex + kPosSize + kUVSize + kColorSize + kNormalSize + kTangentSize;
    _vertexData[subIndex++] = bitangent.x;
    _vertexData[subIndex++] = bitangent.y;
    _vertexData[subIndex++] = bitangent.z;
}

int PrimObject::GetVertexStride() const
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

void PrimObject::Commit()
{
    assert(_vertexData.size() > 0);
    
    unsigned int stride = GetVertexStride();
    
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    
    
    glBindVertexArray(_vao);
    {
        CommitVBO(stride);
        if(_bEnableEBO)
        {
            glGenBuffers(1,&_ebo);
            CommitEBO();
        }
    }
    glBindVertexArray(0);
}

void PrimObject::CommitVBO(int stride)
{
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    {
        // pass data to vbo
        assert(_vertexData.size() > 0);
        unsigned long bufferSize = sizeof(_vertexData[0]) * _vertexData.size();
        void* bufferAddress = &_vertexData[0];
        glBufferData(GL_ARRAY_BUFFER,bufferSize,bufferAddress,GL_STATIC_DRAW);
        
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

void PrimObject::CommitEBO()
{
    assert(_indexData.size() > 0);
    const unsigned long bufferSize = sizeof(_indexData[0]) * _indexData.size();
    const void* bufferAddress = &_indexData[0];
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, bufferAddress, GL_STATIC_DRAW);
    }
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);  // must keep EBO bound !
}

GLuint PrimObject::GetVAO() const
{
    return _vao;
}

int PrimObject::GetVerticesCount() const
{
    return (int)_vertexData.size() / GetVertexStride();
}

int PrimObject::GetIndicesCount() const
{
    return (int)_indexData.size();
}

void PrimObject::SetIndexData(const std::vector<int>& indexData)
{
    // todo
    // do more check
    _indexData = indexData;
}

}

