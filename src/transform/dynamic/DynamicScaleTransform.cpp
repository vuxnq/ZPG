#include "transform/dynamic/DynamicScaleTransform.h"
#include <glm/gtc/matrix_transform.hpp>

DynamicScaleTransform::DynamicScaleTransform(const float growth, const float speed)
: growth(growth), speed(speed) {}

void DynamicScaleTransform::Update(const float delta) {
    scale += growth * speed * delta;
}

glm::mat4 DynamicScaleTransform::GetMatrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
}
