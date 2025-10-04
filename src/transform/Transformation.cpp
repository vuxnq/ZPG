#include "transform/Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

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
