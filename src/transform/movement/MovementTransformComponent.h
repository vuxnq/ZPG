#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class MovementTransformComponent : public TransformComponent {
public:
    MovementTransformComponent(float duration) : duration(duration) {};

protected:
    float duration;
    float elapsed = 0;
};
