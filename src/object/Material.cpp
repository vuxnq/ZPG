#include "object/Material.h"

void Material::SetTexture(GLuint texture) {
    this->texture = texture;
}

void Material::Apply(const ref<ShaderProgram>& shaderProgram) {
    shaderProgram->Use();

    if (texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        shaderProgram->SetUniform("diffuseTexture", 0);
        shaderProgram->SetUniform("useDiffuseTexture", true);
    } else {
        shaderProgram->SetUniform("useDiffuseTexture", false);
    }

    shaderProgram->SetUniform("material.ambient", props.ambient);
    shaderProgram->SetUniform("material.diffuse", props.diffuse);
    shaderProgram->SetUniform("material.specular", props.specular);
    shaderProgram->SetUniform("material.shininess", props.shininess);
    shaderProgram->UnUse();
}
