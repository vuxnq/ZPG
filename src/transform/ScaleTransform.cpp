#include "transform/ScaleTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ScaleTransform::ScaleTransform(const float scale) : scale(scale) {}

glm::mat4 ScaleTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
    cached = true;
    return cachedMatrix;
}
