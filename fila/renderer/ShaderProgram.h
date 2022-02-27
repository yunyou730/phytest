#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

namespace fl {

class ShaderProgram
{
public:
    static ShaderProgram* CreateShaderProgram(const std::string& vsSource,const std::string& fsSource);
    ~ShaderProgram();
    
    void Use();
    void UnUse();
    
    void SetUniformVec4(const std::string& uniformName,const glm::vec4& value);
    void SetUniformVec3(const std::string& uniformName,const glm::vec3& value);
    void SetUniformVec2(const std::string& uniformName,const glm::vec2& value);
    void SetUniformFloat(const std::string& uniformName,float value);
    void SetUniformInt(const std::string& uniformName,int value);
    void SetUniformBool(const std::string& uniformName,bool bValue);
    void SetUniformMat4x4(const std::string& uniformName,float* data);
    void SetUniformMat4x4Array(const std::string& uniformName,unsigned int count,float* data);
    
    bool CheckUniform(const std::string& uniformName);
    
protected:
    ShaderProgram();
    
public:
    GLuint program = 0;
    GLuint vs = 0;
    GLuint fs = 0;
};

}

