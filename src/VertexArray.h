#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"
#include "Core.h"

class VertexArray {
public:
    VertexArray(const ref<VertexBuffer>& vertexBuffer);
    ~VertexArray() {}

	void Bind();
    void Unbind();
    void SetVertexBuffer(const ref<VertexBuffer>& vertexBuffer);

    const VertexBuffer& GetVertexBuffer() const { return *vertexBuffer; }

private:
    GLuint id;
    ref<VertexBuffer> vertexBuffer;
};