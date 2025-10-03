#pragma once
#include <GL/glew.h>
#include "Core.h"
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
public:
    DrawableObject(const ref<Model>& model, const ref<TransformationComponent>& transformation) : model(model), transformation(transformation) {}
    ~DrawableObject() {}

    void SetShaderProgram(const ref<ShaderProgram>& shaderProgram) {
        this->shaderProgram = shaderProgram;
    }
    void Update(float delta) {
        transformation->Update(delta);
    }
    void Draw() {
        model->Bind();
        if (shaderProgram) {
            shaderProgram->SetUniform("modelMatrix", transformation->GetMatrix());
        }
        const auto& vertexBuffer = model->GetVertexArray().GetVertexBuffer();
        GLsizei count = vertexBuffer.GetSize() / vertexBuffer.GetStride();

		glDrawArrays(GL_TRIANGLES, 0, count);
    }

private:
    ref<Model> model;
    ref<TransformationComponent> transformation;
    ref<ShaderProgram> shaderProgram = nullptr;
};