#include "VertexArray.h"

VertexArray::VertexArray(VertexBuffer& vertexBuffer) : vertexBuffer(vertexBuffer) {
    glGenVertexArrays(1, &id);

    SetVertexBuffer(vertexBuffer);
}

void VertexArray::Bind() {
    glBindVertexArray(id);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}

void VertexArray::SetVertexBuffer(VertexBuffer& vertexBuffer) {
	Bind();
    vertexBuffer.Bind();

    auto layout = vertexBuffer.GetLayout();

	size_t stride = 0;
    for (int i = 0; i < layout.size(); i++) {
		stride += get<1>(layout[i]) * ElementType::SizeOf(get<0>(layout[i]));
	}

	int offset = 0;
    for (int i = 0; i < layout.size(); i++) {
		auto& [type, size] = layout[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,  // index
			size,  // size
			ElementType::GlTypeOf(type),  // type
			GL_FALSE,  // normalized
			stride,  // stride
			reinterpret_cast<void*>(offset)  // pointer
		);
		offset += size * ElementType::SizeOf(type);
    }

	Unbind();
    vertexBuffer.Unbind();
}