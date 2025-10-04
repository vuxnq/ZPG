#include "transform/Transformation.h"
#include <iostream>

ScaleTransform::ScaleTransform(const float scale) : scale(scale) {}

glm::mat4 ScaleTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
    cached = true;
    return cachedMatrix;
}

TranslateTransform::TranslateTransform(const glm::vec3& offset) : offset(offset) {}

glm::mat4 TranslateTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::translate(glm::mat4(1.0f), offset);
    cached = true;
    return cachedMatrix;
}

RotateTransform::RotateTransform(const float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 RotateTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::normalize(axis));
    cached = true;
    return cachedMatrix;
}

void Transformation::Add(const ref<TransformComponent>& transformation) {
    children.push_back(transformation);
}

glm::mat4 Transformation::GetMatrix() {
    glm::mat4 matrix = glm::mat4(1.0f);

    for (auto child : children) {
        matrix = child->GetMatrix() * matrix;
    }

    return matrix;
}

void Transformation::Update(const float delta) {
    for (auto child : children) {
        child->Update(delta);
    }
}

DynamicScaleTransform::DynamicScaleTransform(const float growth, const float speed) : growth(growth), speed(speed) {}

void DynamicScaleTransform::Update(const float delta) {
    scale += growth * speed * delta;
}

glm::mat4 DynamicScaleTransform::GetMatrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
}

DynamicTranslateTransform::DynamicTranslateTransform(const glm::vec3& drift, const float speed) : drift(drift), speed(speed) {}

void DynamicTranslateTransform::Update(const float delta) {
    offset += drift * speed * delta;
}

glm::mat4 DynamicTranslateTransform::GetMatrix() {
    return glm::translate(glm::mat4(1.0f), offset);
}

DynamicRotateTransform::DynamicRotateTransform(const float spin, const glm::vec3& axis, const float speed) : spin(spin), axis(glm::normalize(axis)), speed(speed) {}

void DynamicRotateTransform::Update(const float delta) {
    angle += spin * speed * delta;
}
glm::mat4 DynamicRotateTransform::GetMatrix() {
    return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}
