#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class StaticTransformComponent : public TransformComponent {
protected:
    glm::mat4 cachedMatrix;
    bool cached = false;
};
