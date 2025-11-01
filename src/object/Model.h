#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "object/VertexArray.h"
#include "object/Mesh.h"
#include "shader/ShaderProgram.h"

class Model {
public:
    Model() {}
    // support single mesh TODO: ahaaawkdhk mam todo jen abych nezapomnel na temp solutions
    Model(const ref<VertexArray>& vertexArray) {
        auto vertexBuffer = vertexArray->GetVertexBuffer();
        auto vertexCount = vertexBuffer.GetSize() / vertexBuffer.GetStride();
        auto material = make_ref(new Material({}));
        auto mesh = make_ref(new Mesh(vertexArray, vertexCount, material));
        meshes.push_back(mesh);
    }
    ~Model() {}

    void AddMesh(const ref<Mesh>& mesh) {
        meshes.push_back(mesh);
    }

    void Draw(const ref<ShaderProgram>& shaderProgram, const glm::mat4& modelMatrix) {
        shaderProgram->Use();
        shaderProgram->SetUniform("modelMatrix", modelMatrix);
        for (auto& mesh : meshes) {
            mesh->Draw(shaderProgram);
        }
    }

    // const VertexArray& GetVertexArray() const { return *vertexArray; }

private:
    // ref<VertexArray> vertexArray;
    std::vector<ref<Mesh>> meshes;
};