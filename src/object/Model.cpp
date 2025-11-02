#include "object/Model.h"

Model::Model(const ref<VertexArray>& vertexArray) {
    auto vertexBuffer = vertexArray->GetVertexBuffer();
    auto material = make_ref(new Material({}));
    auto mesh = make_ref(new Mesh(vertexArray, material));
    meshes.push_back(mesh);
}

void Model::Draw(const ref<ShaderProgram>& shaderProgram, const glm::mat4& modelMatrix) {
    shaderProgram->Use();
    shaderProgram->SetUniform("modelMatrix", modelMatrix);
    for (auto& mesh : meshes) {
        mesh->Draw(shaderProgram);
    }
}
