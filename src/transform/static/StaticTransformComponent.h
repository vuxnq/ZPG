#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class StaticTransformComponent : public TransformComponent {
public:
    void SetMatrix(const glm::mat4& matrix) { cachedMatrix = matrix; cached = true;};

protected:
    glm::mat4 cachedMatrix;
    bool cached = false;
};
