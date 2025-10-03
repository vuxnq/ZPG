#pragma once
#include <GL/glew.h>
#include "Core.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Transformation.h"

class Model {
public:
    Model(const ref<VertexArray>& vertexArray);
    ~Model() {}

    void Bind();
    const VertexArray& GetVertexArray() const { return *vertexArray; }

private:
    ref<VertexArray> vertexArray;
};