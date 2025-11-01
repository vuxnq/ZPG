#include "object/Material.h"

void Material::Apply(const ref<ShaderProgram>& shaderProgram) {
    shaderProgram->Use();
    shaderProgram->SetUniform("material.ambient", props.ambient);
    shaderProgram->SetUniform("material.diffuse", props.diffuse);
    shaderProgram->SetUniform("material.specular", props.specular);
    shaderProgram->SetUniform("material.shininess", props.shininess);
    shaderProgram->UnUse();
}
