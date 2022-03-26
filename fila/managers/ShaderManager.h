#pragma once
#include <map>
#include <string>

namespace fl {

enum class EBuiltinShaderId
{
    BuiltinAttrPos = 1,
    BuiltinAttrPosUV,
    BuiltinAttrPosUVCol,
    
    Builtin_StardardMVP,
    Builtin_Phy2dDebug,
    
    Max,
};

class ShaderProgram;
class ShaderManager
{
public:
    static ShaderManager* Instance()
    {
        static ShaderManager instance;
        return &instance;
    }
protected:
    ShaderManager() {}
    
    
public:
    void StartUp();
    void CleanUp();
    
    unsigned int CreateShaderWithFile(const std::string& vsPath,const std::string& fsPath);
    unsigned int CreateShader(const std::string& vsCode,const std::string& fsCode);
    ShaderProgram* GetShader(unsigned int shaderId) const;
    
protected:
    void CreateBuiltinShaders();
    
protected:
    std::map<unsigned int,ShaderProgram*>   _shaderCache;
    unsigned int _shaderIdSeed = 0;
    
};
}
