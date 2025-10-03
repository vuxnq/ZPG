#pragma once
#include <GL/glew.h>
#include <VertexBuffer.h>
#include <VertexArray.h>

class Model {
private:
    VertexBuffer vertexBuffer;
    VertexArray vertexArray;
public:
    // TODO: pos vec3, color vec4
    Model(const float vertices[]);
};