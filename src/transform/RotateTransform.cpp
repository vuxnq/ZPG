#include "transform/RotateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

RotateTransform::RotateTransform(const float angle, const glm::vec3& axis)
: angle(angle), axis(axis) {}

glm::mat4 RotateTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::normalize(axis));
    cached = true;
    return cachedMatrix;
}
