#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include "transform/movement/MovementTransformComponent.h"

struct CubicCurve {
    glm::vec3 point1;
    glm::vec3 point2;
    glm::vec3 point3;
    glm::vec3 point4;

    glm::mat3x4 GetMatrix() const {
        return glm::transpose(glm::mat4x3(point1, point2, point3, point4));
    }
};

class BezierTransform : public MovementTransformComponent {
public:
    BezierTransform(const std::vector<CubicCurve>& spline, const float duration, const bool rotate = true, const bool loop = false);
    ~BezierTransform() {}

    glm::mat4 GetMatrix() const override;

private:
    std::vector<CubicCurve> spline;
};
