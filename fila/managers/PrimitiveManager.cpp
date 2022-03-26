#include "PrimitiveManager.h"
#include "PrimObject.h"

namespace fl {
void PrimitiveManager::StartUp()
{
    BuildBuiltins();
}

void PrimitiveManager::CleanUp()
{
    
}

PrimObject* PrimitiveManager::GetPrimObject(EPrimitiveType primType) const
{
    auto it = _primMap.find(primType);
    if(it != _primMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void PrimitiveManager::BuildBuiltins()
{
    BuildQuad();
    BuildCube();
}

void PrimitiveManager::BuildQuad()
{
    auto po = new PrimObject(fl::EVertexAttrType::POS_UV_COLOR,true);
    po->AddVertex(glm::vec3(-0.5,-0.5,0.0),glm::vec2(0,0),glm::vec3(1,0,0));
    po->AddVertex(glm::vec3( 0.5,-0.5,0.0),glm::vec2(1,0),glm::vec3(0,1,0));
    po->AddVertex(glm::vec3(-0.5, 0.5,0.0),glm::vec2(0,1),glm::vec3(0,0,1));
    po->AddVertex(glm::vec3( 0.5, 0.5,0.0),glm::vec2(1,1),glm::vec3(1,1,0));
    po->SetIndexData({0,1,2,1,3,2});
    po->Commit();
    
    _primMap.insert(std::make_pair(EPrimitiveType::Quad,po));
}

void PrimitiveManager::BuildCube()
{
    auto po = new PrimObject(fl::EVertexAttrType::POS_UV_COLOR,true);
    
    // near
    po->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    po->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    po->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    po->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));

    // far
    po->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    po->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    po->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    po->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));

    // left
    po->AddVertex(glm::vec3(-0.5,-0.5, 0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    po->AddVertex(glm::vec3(-0.5,-0.5,-0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    po->AddVertex(glm::vec3(-0.5, 0.5, 0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    po->AddVertex(glm::vec3(-0.5, 0.5,-0.5),glm::vec2(1,1),glm::vec3(1,1,0));

    // right
    po->AddVertex(glm::vec3( 0.5,-0.5,-0.5),glm::vec2(0,0),glm::vec3(1,0,0));
    po->AddVertex(glm::vec3( 0.5,-0.5, 0.5),glm::vec2(1,0),glm::vec3(0,1,0));
    po->AddVertex(glm::vec3( 0.5, 0.5,-0.5),glm::vec2(0,1),glm::vec3(0,0,1));
    po->AddVertex(glm::vec3( 0.5, 0.5, 0.5),glm::vec2(1,1),glm::vec3(1,1,0));

    // top & bottom
    // todo

    po->SetIndexData({
        0,1,2,1,2,3,        // near
        4,5,6,5,6,7,        // far
        8,9,10,9,10,11,      // left
        12,13,14,13,14,15,  // right

    });
    po->Commit();

    
    _primMap.insert(std::make_pair(EPrimitiveType::Cube,po));
}

}

