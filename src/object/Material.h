#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "core/Core.h"
#include "shader/ShaderProgram.h"

struct MaterialProps {
    glm::vec3 ambient = glm::vec3(0.0);
    glm::vec3 diffuse = glm::vec3(1.0);
    glm::vec3 specular = glm::vec3(1.0);
    float shininess = 32.0;
};

class Material {
public:
    Material(const MaterialProps& props) : props(props) {}
    ~Material() {}

    void Apply(const ref<ShaderProgram>& shaderProgram) {
        shaderProgram->SetUniform("material.ambient", props.ambient);
        shaderProgram->SetUniform("material.diffuse", props.diffuse);
        shaderProgram->SetUniform("material.specular", props.specular);
        shaderProgram->SetUniform("material.shininess", props.shininess);
    }

private:
    MaterialProps props;
};
