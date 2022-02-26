#include "ShaderProgram.h"
#include <cassert>

namespace fl {

static void glCheckError()
{
    
}

ShaderProgram::ShaderProgram()
{
    
}

ShaderProgram* ShaderProgram::CreateShaderProgram(const std::string& vsSource,const std::string& fsSource)
{
    const char* vsSourceAlias = vsSource.c_str();
    const char* fsSourceAlias = fsSource.c_str();
    
    ShaderProgram* shader = new ShaderProgram();
    int success = 0;
    
    // vs
    shader->vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vs,1,&vsSourceAlias,nullptr);
    glCompileShader(shader->vs);
    
    char infoLog[512];
    glGetShaderiv(shader->vs,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader->vs,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        
        assert(false);
    }
    
    // fs
    shader->fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fs,1,&fsSourceAlias,nullptr);
    glCompileShader(shader->fs);
    glGetShaderiv(shader->fs,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader->fs,512,nullptr,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        
        assert(false);
    }
    
    // program
    shader->program = glCreateProgram();
    glAttachShader(shader->program,shader->vs);
    glAttachShader(shader->program,shader->fs);
    glLinkProgram(shader->program);
    glGetProgramiv(shader->program,GL_LINK_STATUS,&success);
    if(!success)
    {
        glGetProgramInfoLog(shader->program,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        
        assert(false);
    }
    
    glDeleteShader(shader->vs);
    glDeleteShader(shader->fs);
    
    shader->vs = 0;
    shader->fs = 0;
    
    return shader;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program);
    program = 0;
}

void ShaderProgram::Use()
{
    glUseProgram(program);
    glCheckError();
}

void ShaderProgram::UnUse()
{
    glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& uniformName,const glm::vec4& value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform4f(location,value.x,value.y,value.z,value.w);
    glCheckError();
}

void ShaderProgram::SetUniform(const std::string& uniformName,const glm::vec3& value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glCheckError();
    glUniform3f(location,value.x,value.y,value.z);
    glCheckError();
//    std::cout << glGetError() << std::endl; // 返回 0 (无错误)

}

void ShaderProgram::SetUniform(const std::string& uniformName,const glm::vec2& value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glCheckError();
    glUniform2f(location,value.x,value.y);
    glCheckError();
}

void ShaderProgram::SetUniform(const std::string& uniformName,float value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform1f(location,value);
    glCheckError();
}

void ShaderProgram::SetUniform(const std::string& uniformName,int value)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform1i(location,value);
    glCheckError();
}

void ShaderProgram::SetUniform(const std::string& uniformName,bool bValue)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    glUniform1ui(location,bValue);
    glCheckError();
}

void ShaderProgram::SetUniformMat4x4(const std::string& uniformName,float* data)
{
    GLint location = glGetUniformLocation(program,uniformName.c_str());
    assert(location >= 0);
    
    // @miao @todo
        /*
         void glUniformMatrix4fv(    GLint      location,
              GLsizei      count,
              GLboolean      transpose,
              const GLfloat *     value);

         */
    // 1 means 1 mat4
    glUniformMatrix4fv(location,1,GL_TRUE,data);
    glCheckError();
}

void ShaderProgram::SetUniformMat4x4Array(const std::string& uniformName,unsigned int count,float* data)
{
    GLuint location = glGetUniformLocation(program,uniformName.c_str());
    glUniformMatrix4fv(location, count, GL_FALSE, data);
    glCheckError();
}

}


