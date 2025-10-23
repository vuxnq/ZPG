#pragma once
#include "object/DrawableObject.h"
#include "light/PointLight.h"

class LightObject : public DrawableObject {
public:
    LightObject(
        const ref<Model>& model,
        const ref<TransformComponent>& transformation,
        const ref<ShaderProgram>& shaderProgram,
        const ref<PointLight>& light
    );

    void Update(float delta) override;

private:
    ref<PointLight> light;
};