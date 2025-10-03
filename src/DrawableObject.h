#pragma once
#include <GL/glew.h>
#include "Core.h"
#include "Model.h"
#include "Transformation.h"
#include "ShaderProgram.h"

class DrawableObject {
public:
    DrawableObject(const ref<Model>& model, const ref<TransformationComponent>& transformation, const ref<ShaderProgram>& shaderProgram);
    ~DrawableObject() {}

    void SetShaderProgram(const ref<ShaderProgram>& shaderProgram);
    void Update(float delta);
    void Draw();

private:
    ref<Model> model;
    ref<TransformationComponent> transformation;
    ref<ShaderProgram> shaderProgram;
};