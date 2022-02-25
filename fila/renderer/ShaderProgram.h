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
    
    void SetUniform(const std::string& uniformName,const glm::vec4& value);
    void SetUniform(const std::string& uniformName,const glm::vec3& value);
    void SetUniform(const std::string& uniformName,const glm::vec2& value);
    void SetUniform(const std::string& uniformName,float value);
    void SetUniform(const std::string& uniformName,int value);
    void SetUniform(const std::string& uniformName,bool bValue);
    void SetUniformMat4x4(const std::string& uniformName,float* data);
    void SetUniformMat4x4Array(const std::string& uniformName,unsigned int count,float* data);
    
public:
    GLuint program = 0;
    GLuint vs = 0;
    GLuint fs = 0;
};

}

