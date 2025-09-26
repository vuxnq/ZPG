#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"

class VertexArray {
private:
    GLuint id;
    VertexBuffer* vertexBuffer;
public:
    VertexArray();
    VertexArray(VertexBuffer* vertexBuffer);
    ~VertexArray();

	void Bind();
    void Unbind();
    void AddVertexBuffer(VertexBuffer& vertexBuffer);
};