#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformationComponent {
public:
    virtual glm::mat4 ComputeMatrix() = 0;
};


class ScaleTransform : public TransformationComponent {
private:
    float scale;
public:
    ScaleTransform(const float scale);
    glm::mat4 ComputeMatrix() override;
};

class TranslateTransform : public TransformationComponent {
private:
    glm::vec3 offset;
public:
    TranslateTransform(const glm::vec3& offset);
    glm::mat4 ComputeMatrix() override;
};

class RotateTransform : public TransformationComponent {
private:
    float angle;
    glm::vec3 axis;
public:
    RotateTransform(float angle, const glm::vec3& axis);
    glm::mat4 ComputeMatrix() override;
};


class Transformation : public TransformationComponent {
private:
    std::vector<TransformationComponent*> children;
public:
    Transformation() {}
    void Add(TransformationComponent* transformation);
    glm::mat4 ComputeMatrix() override;
};
