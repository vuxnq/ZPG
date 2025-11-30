#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class MovementTransformComponent : public TransformComponent {
public:
    MovementTransformComponent(const float duration, const bool rotate = true, const bool loop = false)
    : duration(duration), rotate(rotate), loop(loop) {};

    void Update(const float delta) override {
        if (loop) elapsed = std::fmod((elapsed + delta), duration);
        else elapsed = std::min(elapsed + delta, duration);
    }

protected:
    float duration;
    bool rotate = true;
    bool loop = false;
    float elapsed = 0;
};
