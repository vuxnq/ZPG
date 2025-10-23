#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "object/Model.h"
#include "transform/Transformation.h"
#include "shader/ShaderProgram.h"

class DrawableObject {
public:
    DrawableObject(const ref<Model>& model, const ref<TransformComponent>& transformation, const ref<ShaderProgram>& shaderProgram);
    ~DrawableObject() {}

    void SetShaderProgram(const ref<ShaderProgram>& shaderProgram);
    void Update(float delta);
    void Draw(); // TODO: renderer

private:
    ref<Model> model;
    ref<TransformComponent> transformation;
    ref<ShaderProgram> shaderProgram;
};