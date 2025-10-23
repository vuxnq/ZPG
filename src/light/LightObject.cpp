#include "light/LightObject.h"

LightObject::LightObject(
    const ref<Model>& model,
    const ref<TransformComponent>& transformation,
    const ref<ShaderProgram>& shaderProgram,
    const ref<PointLight>& light
) : DrawableObject(model, transformation, shaderProgram) {
    this->light = light;
    this->light->SetPosition(glm::vec3(transformation->GetMatrix()[3]));
}

void LightObject::Update(float delta) {
    DrawableObject::Update(delta);
    glm::vec3 newPosition = glm::vec3(transformation->GetMatrix()[3]);
    if (light->GetPosition() != newPosition) light->SetPosition(newPosition);
}