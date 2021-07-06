#include "shaderProgram.hpp"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram()
{
    m_ProgramId = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramId);
}
void ShaderProgram::link()
{
    glLinkProgram(m_ProgramId);
    int isLinked;
    char log[512];
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        glGetProgramInfoLog(isLinked,512,0,log);
        std::cout<<"ERROR: Shader Program could not linked"<<std::endl<<log<<std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(m_ProgramId);
}

void ShaderProgram::attachShader(const char *fileName, unsigned int shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);
    std::string sourceCode = getShaderFromFile(fileName);
    const char *chSourceCode = &sourceCode[0];

    glShaderSource(shaderId, 1, &chSourceCode, 0);
    glCompileShader(shaderId);
    int isCompiled;
    char log[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        glad_glGetShaderInfoLog(shaderId,512,0,log);
        std::cout<<"ERROR:"<<fileName<<std::endl<<log<<std::endl;
    }
    glAttachShader(m_ProgramId, shaderId);
    glDeleteShader(shaderId);
}

std::string ShaderProgram::getShaderFromFile(const char *fileName)
{
    std::ifstream file(fileName);
    std::string data;
    if (file.is_open())
    {
        char readChar;
        while ((readChar = file.get()) != EOF)
        {
            data += readChar;
        }
    }
    return data;
}