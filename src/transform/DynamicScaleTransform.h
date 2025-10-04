#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "transform/TransformComponent.h"

class DynamicScaleTransform : public TransformComponent {
public:
    DynamicScaleTransform(const float growth, const float speed);
    ~DynamicScaleTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    float scale = 1;
    float growth;
    float speed;
};
