#include "shaderProgram.hpp"
#include <glad/glad.h>
#include <fstream>

ShaderProgram::ShaderProgram()
{
    m_ProgramId = glCreateProgram();
}
void ShaderProgram::link()
{
    glLinkProgram(m_ProgramId);
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
    glAttachShader(m_ProgramId, shaderId);
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