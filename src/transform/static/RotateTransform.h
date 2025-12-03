#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/static/StaticTransformComponent.h"

class RotateTransform : public StaticTransformComponent {
public:
    RotateTransform(const float angle, const glm::vec3& axis);
    ~RotateTransform() {}

private:
    float angle;
    glm::vec3 axis;
};
