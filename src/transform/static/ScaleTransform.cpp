#include "transform/static/ScaleTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ScaleTransform::ScaleTransform(const float scale)
: scale(scale) {
    cachedMatrix = glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
}
