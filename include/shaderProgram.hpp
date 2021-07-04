#ifndef SHADERPROGRAM_HPP
#define SAHADERPROGRAM_HPP

#include <string>
class ShaderProgram
{
public:
    ShaderProgram();

    ~ShaderProgram();
    
    void attachShader(const char *fileName, unsigned int shaderType);

    void link();

    void use();

private:
    unsigned int m_ProgramId;
    std::string getShaderFromFile(const char *fileName);
};

#endif