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

    glm::mat3x4 GetMatrix() {
        return glm::transpose(glm::mat4x3(point1, point2, point3, point4));
    }
};

class BezierTransform : public MovementTransformComponent {
public:
    BezierTransform(const std::vector<CubicCurve>& spline, const float duration, const float loop = false);
    ~BezierTransform() {}

    glm::mat4 GetMatrix() override;

private:
    std::vector<CubicCurve> spline;

    glm::mat4 bezierMatrix = glm::mat4(
        glm::vec4(-1.0,  3.0, -3.0, 1.0),
        glm::vec4( 3.0, -6.0,  3.0, 0.0),
        glm::vec4(-3.0,  3.0,  0.0, 0.0),
        glm::vec4( 1.0,  0.0,  0.0, 0.0)
    );
};
