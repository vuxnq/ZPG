#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core.h"
#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram(const std::vector<ref<Shader>>& shaders);
    ~ShaderProgram() {}

    void Use();
    void UnUse();

    void SetUniform(const std::string& name, const glm::mat4& value);
    // TODO: overloading

private:
    GLuint id;
    // std::vector<ref<Shader>> shaders;

    int GetUniformLocation(const std::string& name);
};
