#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <core/Core.h>
#include "transform/TransformComponent.h"

#include "transform/DynamicRotateTransform.h"
#include "transform/DynamicScaleTransform.h"
#include "transform/DynamicTranslateTransform.h"

#include "transform/RotateTransform.h"
#include "transform/ScaleTransform.h"
#include "transform/TranslateTransform.h"

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
