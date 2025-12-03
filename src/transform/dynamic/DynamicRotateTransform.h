#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class DynamicRotateTransform : public TransformComponent {
public:
    DynamicRotateTransform(const float spin, const glm::vec3& axis, const float speed);
    ~DynamicRotateTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() const override;

private:
    float angle = 0;
    float spin;
    glm::vec3 axis;
    float speed;
};
