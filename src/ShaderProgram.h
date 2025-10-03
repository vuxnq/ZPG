#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class ShaderProgram {
private:
    GLuint id;

public:
    ShaderProgram(const std::vector<Shader*>& shaders);
    ~ShaderProgram();

    void Use();
    void UnUse();

    void SetUniform(const std::string& name, const glm::mat4& value);
    // TODO: overloading
private:
    int GetUniformLocation(const std::string& name);
};

std::string ReadShaderSource(const std::string& filePath);