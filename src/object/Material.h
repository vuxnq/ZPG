#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

struct MaterialProps {
    glm::vec3 ambient = glm::vec3(0.0);
    glm::vec3 diffuse = glm::vec3(1.0);
    glm::vec3 specular = glm::vec3(1.0);
};

class Material {
public:
    Material(const MaterialProps& props);
    ~Material() {}

private:
    MaterialProps props;
};
