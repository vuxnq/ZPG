#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/Core.h"
#include "core/Observer.h"
#include "core/Shader.h"

class ShaderProgram : public Subscriber {
public:
    ShaderProgram(const std::vector<ref<Shader>>& shaders);
    ~ShaderProgram() {}

    void Use();
    void UnUse();

    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, int value);

    void SetUniform(const std::string& name, const glm::vec2& value);
    void SetUniform(const std::string& name, const glm::vec3& value);
    void SetUniform(const std::string& name, const glm::vec4& value);

    void SetUniform(const std::string& name, const glm::mat2& value);
    void SetUniform(const std::string& name, const glm::mat3& value);
    void SetUniform(const std::string& name, const glm::mat4& value);

    void OnNotify(const Event& event) override;

private:
    GLuint id;

    int GetUniformLocation(const std::string& name);

    // TODO: kurva pico
    inline static int lightcount = 0;

};
