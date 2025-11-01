#pragma once
#include <GL/glew.h>
#include "object/VertexArray.h"
#include "object/Material.h"
#include "shader/ShaderProgram.h"

class Mesh {
public:
    Mesh(const ref<VertexArray>& vertexArray, const ref<Material>& material) : vertexArray(vertexArray), material(material) {}
    ~Mesh() {}

    void Draw(const ref<ShaderProgram>& shaderProgram);

private:
    ref<VertexArray> vertexArray;
    ref<Material> material = nullptr;
};
