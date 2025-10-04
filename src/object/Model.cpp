#include "object/Model.h"

Model::Model(const ref<VertexArray>& vertexArray) : vertexArray(vertexArray) {}

void Model::Bind() {
    vertexArray->Bind();
}