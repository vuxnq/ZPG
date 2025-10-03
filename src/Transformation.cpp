#include "Transformation.h"
#include <iostream>

ScaleTransform::ScaleTransform(float scale) : scale(scale) {}

glm::mat4 ScaleTransform::ComputeMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
    cached = true;
    return cachedMatrix;
}

TranslateTransform::TranslateTransform(const glm::vec3& offset) : offset(offset) {}

glm::mat4 TranslateTransform::ComputeMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::translate(glm::mat4(1.0f), offset);
    cached = true;
    return cachedMatrix;
}

RotateTransform::RotateTransform(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 RotateTransform::ComputeMatrix() {
    if (cached) {
        return cachedMatrix;
    }
    cachedMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::normalize(axis));
    cached = true;
    return cachedMatrix;
}

void Transformation::Add(TransformationComponent* transformation) {
    children.push_back(transformation);
}

glm::mat4 Transformation::ComputeMatrix() {
    glm::mat4 matrix = glm::mat4(1.0f);

    for (TransformationComponent* child : children) {
        matrix = child->ComputeMatrix() * matrix;
    }

    return matrix;
}

void Transformation::Update(float delta) {
    for (TransformationComponent* child : children) {
        child->Update(delta);
    }
}

DynamicRotateTransform::DynamicRotateTransform(float startAngle, float speed, const glm::vec3& axis): axis(glm::normalize(axis)), angle(startAngle), speed(speed) {}

void DynamicRotateTransform::Update(float delta) {
    angle += speed * delta;
}
glm::mat4 DynamicRotateTransform::ComputeMatrix() {
    return glm::rotate(glm::mat4(1.f), glm::radians(angle), axis);
}
