#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void SetUniform(const std::string& name, const glm::mat4& value);
    // TODO: overloading
};

std::string ReadShaderSource(const std::string& filePath);