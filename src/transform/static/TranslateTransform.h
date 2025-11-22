#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/static/StaticTransformComponent.h"

class TranslateTransform : public StaticTransformComponent {
public:
    TranslateTransform(const glm::vec3& offset);
    ~TranslateTransform() {}

    glm::mat4 GetMatrix() override;

private:
    glm::vec3 offset;
};
