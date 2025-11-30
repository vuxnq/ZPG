#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <core/Core.h>
#include "transform/TransformComponent.h"

#include "transform/dynamic/DynamicRotateTransform.h"
#include "transform/dynamic/DynamicScaleTransform.h"
#include "transform/dynamic/DynamicTranslateTransform.h"

#include "transform/static/RotateTransform.h"
#include "transform/static/ScaleTransform.h"
#include "transform/static/TranslateTransform.h"

#include "transform/movement/PolylineTransform.h"
#include "transform/movement/BezierTransform.h"

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
