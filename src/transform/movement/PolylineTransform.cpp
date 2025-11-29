#include "transform/movement/PolylineTransform.h"
#include <glm/gtc/matrix_transform.hpp>

PolylineTransform::PolylineTransform(const std::vector<glm::vec3>& points, const float duration)
: MovementTransformComponent(duration), points(points) {}

void PolylineTransform::Update(const float delta) {
    elapsed = std::min(elapsed + delta, duration);
}

glm::mat4 PolylineTransform::GetMatrix() {
    if (points.empty()) return glm::mat4(1.0f);
    if (points.size() == 1) return glm::translate(glm::mat4(1.0f), points[0]);

    float time = elapsed / duration;

    int segCount = points.size() - 1;
    float scaled = time * segCount;
    // TODO: kdyz 3 segmenty a time = 0.5 -> scaled = 1.5 -> v pulce v 1. indexu

    float index = std::floor(scaled);
    if (index >= segCount) index = segCount - 1;

    float localTime = scaled - index;

    glm::vec3 a = points[index];
    glm::vec3 b = points[index + 1];
    glm::vec3 pos = (1 - localTime) * a + localTime * b;

    return glm::translate(glm::mat4(1.0f), pos);
}
