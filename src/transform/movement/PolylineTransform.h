#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "transform/movement/MovementTransformComponent.h"

class PolylineTransform : public MovementTransformComponent {
public:
    PolylineTransform(const std::vector<glm::vec3>& points, const float duration, const bool rotate = true, const bool loop = false);
    ~PolylineTransform() {}

    glm::mat4 GetMatrix() const override;

private:
    std::vector<glm::vec3> points;
};
