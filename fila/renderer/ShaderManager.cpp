#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "FileReader.h"

namespace fl {

ShaderManager::ShaderManager()
{
    CreateBuiltinShaders();
}

unsigned int ShaderManager::CreateShaderWithFile(const std::string& vsPath,const std::string& fsPath)
{
    FileReader vsReader(vsPath);
    FileReader fsReader(fsPath);
    unsigned int shaderId = CreateShader(vsReader.Read(),fsReader.Read());
    return shaderId;
}

unsigned int ShaderManager::CreateShader(const std::string& vsCode,const std::string& fsCode)
{
    auto program = ShaderProgram::CreateShaderProgram(vsCode,fsCode);
    unsigned int shaderId = ++_shaderIdSeed;
    _shaderCache.insert(std::make_pair(shaderId,program));
    return shaderId;
}

void ShaderManager::CreateBuiltinShaders()
{
    CreateShaderWithFile("res/attr_pos.vsh","res/attr_pos.fsh");
    CreateShaderWithFile("res/attr_pos_uv.vsh","res/attr_pos_uv.fsh");
    CreateShaderWithFile("res/attr_pos_uv_col.vsh","res/attr_pos_uv_col.fsh");
    CreateShaderWithFile("res/standard_mvp.vsh","res/standard_mvp.fsh");
    CreateShaderWithFile("res/phy2d_debug.vsh","res/phy2d_debug.fsh");
}

ShaderProgram* ShaderManager::GetShader(unsigned int shaderId) const
{
    ShaderProgram* program = nullptr;
    auto it = _shaderCache.find(shaderId);
    if(it != _shaderCache.end())
    {
        program = it->second;
    }
    return program;
}

}
