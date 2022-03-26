#pragma once

#include <glad/glad.h>
#include <map>

namespace fl {

enum class EPrimitiveType
{
    Quad,
    Cube,
    
    Max,
};

class PrimObject;

class PrimitiveManager
{
public:
    static PrimitiveManager* Instance()
    {
        static PrimitiveManager instance;
        return &instance;
    }
protected:
    PrimitiveManager() {}
    
public:
    void StartUp();
    void CleanUp();
    
    PrimObject* GetPrimObject(EPrimitiveType primType) const;
    
protected:
    void BuildBuiltins();
    
    void BuildQuad();
    void BuildCube();
    
protected:
    std::map<EPrimitiveType,PrimObject*>   _primMap;
    
};



}
