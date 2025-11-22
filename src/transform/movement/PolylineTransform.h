#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "transform/movement/MovementTransformComponent.h"

class PolylineTransform : public MovementTransformComponent {
public:
    PolylineTransform(const std::vector<glm::vec3>& points, const float duration);
    ~PolylineTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    std::vector<glm::vec3> points;
};
