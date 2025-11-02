#include "object/DrawableObject.h"

DrawableObject::DrawableObject(const ref<Model>& model, const ref<TransformComponent>& transformation, const ref<ShaderProgram>& shaderProgram)
: model(model), transformation(transformation), shaderProgram(shaderProgram) {}

void DrawableObject::SetShaderProgram(const ref<ShaderProgram>& shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void DrawableObject::Update(float delta) {
    transformation->Update(delta);
}

void DrawableObject::Draw() {
    if (shaderProgram == nullptr) {
        fprintf(stderr, "Shader program must be set.");
        exit(EXIT_FAILURE);
    }

    model->Draw(shaderProgram, transformation->GetMatrix());
}
