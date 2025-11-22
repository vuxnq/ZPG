#include "transform/static/TranslateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

TranslateTransform::TranslateTransform(const glm::vec3& offset)
: offset(offset) {}

glm::mat4 TranslateTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::translate(glm::mat4(1.0f), offset);
    cached = true;
    return cachedMatrix;
}
