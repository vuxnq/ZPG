#include "object/VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const float vertices[], size_t size, std::vector<std::tuple<ElementType::Type, int>> layout) : size(size), layout(layout) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const std::vector<std::tuple<ElementType::Type, int>>& VertexBuffer::GetLayout() const {
	return layout;
}

void VertexBuffer::SetLayout(std::vector<std::tuple<ElementType::Type, int>> layout) {
	this->layout = layout;
}

int VertexBuffer::GetStride() const {
	size_t stride = 0;
    for (int i = 0; i < layout.size(); i++) {
		stride += get<1>(layout[i]) * ElementType::SizeOf(get<0>(layout[i]));
	}
    return stride;
}
