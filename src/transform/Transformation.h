#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Core.h"

class TransformComponent {
public:
    virtual glm::mat4 GetMatrix() = 0;
    virtual void Update(float delta) {}
};


class StaticTransformComponent : public TransformComponent {
protected:
    glm::mat4 cachedMatrix;
    bool cached = false;
};


class ScaleTransform : public StaticTransformComponent {
public:
    ScaleTransform(const float scale);
    ~ScaleTransform() {}

    glm::mat4 GetMatrix() override;

private:
    float scale;
};

class TranslateTransform : public StaticTransformComponent {
public:
    TranslateTransform(const glm::vec3& offset);
    ~TranslateTransform() {}

    glm::mat4 GetMatrix() override;

private:
    glm::vec3 offset;
};

class RotateTransform : public StaticTransformComponent {
public:
    RotateTransform(const float angle, const glm::vec3& axis);
    ~RotateTransform() {}

    glm::mat4 GetMatrix() override;

private:
    float angle;
    glm::vec3 axis;
};

class DynamicScaleTransform : public TransformComponent {
public:
    DynamicScaleTransform(const float growth, const float speed);
    ~DynamicScaleTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    float scale = 1;
    float growth;
    float speed;
};

class DynamicTranslateTransform : public TransformComponent {
public:
    DynamicTranslateTransform(const glm::vec3& direction, const float speed);
    ~DynamicTranslateTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    glm::vec3 offset = glm::vec3(0.0f);
    glm::vec3 drift;
    float speed;
};

class DynamicRotateTransform : public TransformComponent {
public:
    DynamicRotateTransform(const float spin, const glm::vec3& axis, const float speed);
    ~DynamicRotateTransform() {}

    void Update(const float delta) override;
    glm::mat4 GetMatrix() override;

private:
    float angle = 0;
    float spin;
    glm::vec3 axis;
    float speed;
};


class Transformation : public TransformComponent {
public:
    Transformation() {}
    ~Transformation() {}

    void Add(const ref<TransformComponent>& transformation);
    glm::mat4 GetMatrix() override;
    void Update(const float delta) override;

private:
    std::vector<ref<TransformComponent>> children;
};
