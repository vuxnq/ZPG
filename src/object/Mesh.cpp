#include "object/Mesh.h"

void Mesh::Draw(const ref<ShaderProgram>& shaderProgram) {
    if (material) material->Apply(shaderProgram);

    shaderProgram->Use();
    vertexArray->Bind();

    glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexCount());

    shaderProgram->UnUse();
}
