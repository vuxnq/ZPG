#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/static/StaticTransformComponent.h"

class ScaleTransform : public StaticTransformComponent {
public:
    ScaleTransform(const float scale);
    ~ScaleTransform() {}

    glm::mat4 GetMatrix() override;

private:
    float scale;
};
