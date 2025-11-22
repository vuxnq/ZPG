#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class DynamicTranslateTransform : public TransformComponent {
public:
    DynamicTranslateTransform(const glm::vec3& direction, const float speed);
    ~DynamicTranslateTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    glm::vec3 offset = glm::vec3(0.0f);
    glm::vec3 drift;
    float speed;
};
