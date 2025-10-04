#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "object/VertexArray.h"

class Model {
public:
    Model(const ref<VertexArray>& vertexArray);
    ~Model() {}

    void Bind();
    const VertexArray& GetVertexArray() const { return *vertexArray; }

private:
    ref<VertexArray> vertexArray;
};