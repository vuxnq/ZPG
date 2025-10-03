#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Transformation.h"

class Model {
public:
    Model(VertexArray& vertexArray);
    ~Model() {}

private:
    VertexArray& vertexArray;
};