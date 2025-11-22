#include "transform/dynamic/DynamicTranslateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

DynamicTranslateTransform::DynamicTranslateTransform(const glm::vec3& drift, const float speed)
: drift(drift), speed(speed) {}

void DynamicTranslateTransform::Update(const float delta) {
    offset += drift * speed * delta;
}

glm::mat4 DynamicTranslateTransform::GetMatrix() {
    return glm::translate(glm::mat4(1.0f), offset);
}
