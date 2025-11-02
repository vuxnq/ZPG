#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "object/VertexArray.h"
#include "object/Mesh.h"
#include "shader/ShaderProgram.h"

class Model {
public:
    Model() {}
    Model(const ref<VertexArray>& vertexArray);
    ~Model() {}

    void AddMesh(const ref<Mesh>& mesh) { meshes.push_back(mesh); }

    void Draw(const ref<ShaderProgram>& shaderProgram, const glm::mat4& modelMatrix);

private:
    std::vector<ref<Mesh>> meshes;
};