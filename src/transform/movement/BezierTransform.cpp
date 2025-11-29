#include "transform/movement/BezierTransform.h"
#include <glm/gtc/matrix_transform.hpp>

BezierTransform::BezierTransform(const std::vector<CubicCurve>& spline, const float duration, const float loop)
: MovementTransformComponent(duration, loop), spline(spline) {}

glm::mat4 BezierTransform::GetMatrix() {
    // TODO: check
    if (spline.empty()) return glm::mat4(1.0f);

    float time = elapsed / duration;

    int curvesCount = spline.size();
    float scaled = time * curvesCount;

    float index = std::floor(scaled);
    if (index >= curvesCount) index = curvesCount - 1;

    float localTime = scaled - index;

    glm::vec4 parameters = glm::vec4(localTime * localTime * localTime, localTime * localTime, localTime, 1.0f);
    glm::vec3 pos = parameters * bezierMatrix * spline[index].GetMatrix();

    // glm::vec3 pos =
    //     (float)pow(1 - localTime, 3) * spline[index].point1 +
    //     3 * (float)pow(1 - localTime, 2) * localTime * spline[index].point2 +
    //     3 * (1 - localTime) * (float)pow(localTime, 2) * spline[index].point3 +
    //     (float)pow(localTime, 3) * spline[index].point4;

    return glm::translate(glm::mat4(1.f), pos);
}
