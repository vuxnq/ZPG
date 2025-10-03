#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core.h"

class TransformationComponent {
public:
    virtual glm::mat4 GetMatrix() = 0;
    virtual void Update(float delta) {}
};


class StaticTransformationComponent : public TransformationComponent {
protected:
    glm::mat4 cachedMatrix;
    bool cached = false;
};


class ScaleTransform : public StaticTransformationComponent {
public:
    ScaleTransform(const float scale);
    ~ScaleTransform() {}

    glm::mat4 GetMatrix() override;

private:
    float scale;
};

class TranslateTransform : public StaticTransformationComponent {
public:
    TranslateTransform(const glm::vec3& offset);
    ~TranslateTransform() {}

    glm::mat4 GetMatrix() override;

private:
    glm::vec3 offset;
};

class RotateTransform : public StaticTransformationComponent {
public:
    RotateTransform(float angle, const glm::vec3& axis);
    ~RotateTransform() {}

    glm::mat4 GetMatrix() override;

private:
    float angle;
    glm::vec3 axis;
};

class DynamicRotateTransform : public TransformationComponent {
public:
    DynamicRotateTransform(float startAngle, float speed, const glm::vec3& axis);
    ~DynamicRotateTransform() {}

    void Update(float delta) override;
    glm::mat4 GetMatrix() override;

private:
    float angle;
    float speed;
    glm::vec3 axis;
};


class Transformation : public TransformationComponent {
public:
    Transformation() {}
    ~Transformation() {}

    void Add(const ref<TransformationComponent>& transformation);
    glm::mat4 GetMatrix() override;
    void Update(float delta) override;

private:
    std::vector<ref<TransformationComponent>> children;
};
