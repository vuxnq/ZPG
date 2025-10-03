#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint id;

    std::string ReadShaderSource(const std::string& shaderSourcePath);
public:
    Shader(const std::string& shaderSourcePath, GLenum shaderType);
};
