#pragma once
#include <GL/glew.h>
#include <string>

class ShaderProgram {
private:
    GLuint id;
    GLuint vertexShader;
    GLuint fragmentShader;
public:
    ShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
    ~ShaderProgram();

    void Use();
    void UnUse();
};

std::string ReadShaderSource(const std::string& filePath);