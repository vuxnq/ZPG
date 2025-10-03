#include "Transformation.h"
#include <iostream>

ScaleTransform::ScaleTransform(float scale) : scale(scale) {}

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

RotateTransform::RotateTransform(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 RotateTransform::GetMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::normalize(axis));
    cached = true;
    return cachedMatrix;
}

void Transformation::Add(const ref<TransformationComponent>& transformation) {
    children.push_back(transformation);
}

glm::mat4 Transformation::GetMatrix() {
    glm::mat4 matrix = glm::mat4(1.0f);

    for (auto child : children) {
        matrix = child->GetMatrix() * matrix;
    }

    return matrix;
}

void Transformation::Update(float delta) {
    for (auto child : children) {
        child->Update(delta);
    }
}

DynamicRotateTransform::DynamicRotateTransform(float startAngle, float speed, const glm::vec3& axis) : axis(glm::normalize(axis)), angle(startAngle), speed(speed) {}

void DynamicRotateTransform::Update(float delta) {
    angle += speed * delta;
}
glm::mat4 DynamicRotateTransform::GetMatrix() {
    return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}
