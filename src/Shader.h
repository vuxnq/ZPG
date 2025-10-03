#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const std::string& shaderSourcePath, GLenum shaderType);
    ~Shader() {}

    void Attach(GLuint programId);

private:
    GLuint id;

    std::string ReadShaderSource(const std::string& shaderSourcePath);
};
