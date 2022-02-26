#pragma once
#include <map>
#include <string>

namespace fl {

enum class EBuiltinShaderId
{
    BuiltinShader1 = 1,
    
    Max,
};

class ShaderProgram;
class ShaderManager
{
public:
    ShaderManager();
    
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
