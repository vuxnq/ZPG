#include "Transformation.h"
#include <iostream>

ScaleTransform::ScaleTransform(float scale) : scale(scale) {}

glm::mat4 ScaleTransform::ComputeMatrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3((float)scale));
}

TranslateTransform::TranslateTransform(const glm::vec3& offset) : offset(offset) {}

glm::mat4 TranslateTransform::ComputeMatrix() {
    return glm::translate(glm::mat4(1.0f), offset);
}

RotateTransform::RotateTransform(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

glm::mat4 RotateTransform::ComputeMatrix() {
    return glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::normalize(axis));
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
