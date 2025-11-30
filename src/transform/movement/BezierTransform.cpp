#include "transform/movement/BezierTransform.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static glm::mat4 bezierCoefficientsMatrix = glm::mat4(
    glm::vec4(-1.0,  3.0, -3.0, 1.0),
    glm::vec4( 3.0, -6.0,  3.0, 0.0),
    glm::vec4(-3.0,  3.0,  0.0, 0.0),
    glm::vec4( 1.0,  0.0,  0.0, 0.0)
);

BezierTransform::BezierTransform(const std::vector<CubicCurve>& spline, const float duration, const bool rotate, const bool loop)
: MovementTransformComponent(duration, rotate, loop), spline(spline) {}

glm::mat4 BezierTransform::GetMatrix() {
    if (spline.empty()) return glm::mat4(1.0f);

    float time = elapsed / duration;

    int curvesCount = spline.size();
    float scaled = time * curvesCount;

    int index = std::floor(scaled);
    index = std::min(index, curvesCount - 1);

    float localTime = scaled - index;

    glm::vec4 timeVector = glm::vec4(localTime * localTime * localTime, localTime * localTime, localTime, 1.0f);
    glm::vec3 pos = timeVector * bezierCoefficientsMatrix * spline[index].GetMatrix();

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    if (rotate) {
        glm::vec4 derivedTimeVector = glm::vec4(3.0f * localTime * localTime, 2.0f * localTime, 1.0f, 0.0f);
        glm::vec3 tangent = derivedTimeVector * bezierCoefficientsMatrix * spline[index].GetMatrix();

        glm::vec3 worldUp = glm::vec3(0, 1, 0);
        glm::vec3 front = glm::normalize(tangent);
        glm::vec3 right = glm::cross(front, worldUp);
        glm::vec3 up = glm::cross(right, front);

        rotationMatrix = glm::mat4(
            glm::vec4(right,   0),
            glm::vec4(up,      0),
            glm::vec4(front,   0),
            glm::vec4(0, 0, 0, 1)
        );
    }

    return glm::translate(glm::mat4(1.f), pos) * rotationMatrix;
}
