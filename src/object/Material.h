#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "core/Core.h"
#include "shader/ShaderProgram.h"

struct MaterialProps {
    glm::vec3 ambient = glm::vec3(1.0);
    glm::vec3 diffuse = glm::vec3(1.0);
    glm::vec3 specular = glm::vec3(1.0);
    float shininess = 32.0;
};

class Material {
public:
    Material(const MaterialProps& props, GLuint texture = 0) : props(props), texture(texture) {}
    ~Material() {}

    void SetTexture(GLuint texture);

    void Apply(const ref<ShaderProgram>& shaderProgram);

private:
    MaterialProps props;
    GLuint texture; // TODO:
};
