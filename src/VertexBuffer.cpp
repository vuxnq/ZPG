#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer(float vertices[], size_t size, std::vector<std::tuple<ElementType::Type, int>> layout) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	this->layout = layout;
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const std::vector<std::tuple<ElementType::Type, int>>& VertexBuffer::GetLayout() {
	return layout;
}

void VertexBuffer::SetLayout(std::vector<std::tuple<ElementType::Type, int>> layout) {
	this->layout = layout;
}