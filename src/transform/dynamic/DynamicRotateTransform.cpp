#include "transform/dynamic/DynamicRotateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

DynamicRotateTransform::DynamicRotateTransform(const float spin, const glm::vec3& axis, const float speed)
: spin(spin), axis(glm::normalize(axis)), speed(speed) {}

void DynamicRotateTransform::Update(const float delta) {
    angle += spin * speed * delta;
}
glm::mat4 DynamicRotateTransform::GetMatrix() const {
    return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}
