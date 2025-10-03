#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"

class VertexArray {
public:
    VertexArray(VertexBuffer& vertexBuffer);
    ~VertexArray();

	void Bind();
    void Unbind();
    void SetVertexBuffer(VertexBuffer& vertexBuffer);

private:
    GLuint id;
    VertexBuffer& vertexBuffer;
};