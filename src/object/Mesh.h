#pragma once
#include <GL/glew.h>
#include "object/VertexArray.h"
#include "object/Material.h"
#include "shader/ShaderProgram.h"

class Mesh {
public:
    Mesh(const ref<VertexArray>& vertexArray, int vertexCount, const ref<Material>& material) : vertexArray(vertexArray), vertexCount(vertexCount), material(material) {}
    ~Mesh() {}

    void Draw(const ref<ShaderProgram>& shaderProgram) {
        if (material) material->Apply(shaderProgram);
        vertexArray->Bind();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

private:
    ref<VertexArray> vertexArray;
    int vertexCount;
    ref<Material> material;
};
