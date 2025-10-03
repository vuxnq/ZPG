#include "DrawableObject.h"

DrawableObject::DrawableObject(const ref<Model>& model, const ref<TransformationComponent>& transformation, const ref<ShaderProgram>& shaderProgram) : model(model), transformation(transformation), shaderProgram(shaderProgram) {}

void DrawableObject::SetShaderProgram(const ref<ShaderProgram>& shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void DrawableObject::Update(float delta) {
    transformation->Update(delta);
}

void DrawableObject::Draw() {
    model->Bind();
    if (shaderProgram) {
        shaderProgram->Use();
        shaderProgram->SetUniform("modelMatrix", transformation->GetMatrix());
    }
    const auto& vertexBuffer = model->GetVertexArray().GetVertexBuffer();
    GLsizei count = vertexBuffer.GetSize() / vertexBuffer.GetStride();

    glDrawArrays(GL_TRIANGLES, 0, count);
}
