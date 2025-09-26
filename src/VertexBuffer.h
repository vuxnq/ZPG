#pragma once
#include <GL/glew.h>
#include <tuple>
#include <vector>

class ElementType {
public:
    enum Type {
        Float,
        Int,
    };

    static int SizeOf(Type type) {
        switch (type) {
            case Float: return sizeof(float);
            case Int: return sizeof(int);
            default: return 0;
        }
    }

    static int GlTypeOf(Type type) {
        switch (type) {
            case Float: return GL_FLOAT;
            case Int: return GL_INT;
            default: return 0;
        }
    }
};

class VertexBuffer {
private:
    GLuint id;
    std::vector<std::tuple<ElementType::Type, int>> layout;
public:
    VertexBuffer(float vertices[], size_t size, std::vector<std::tuple<ElementType::Type, int>> layout = {});
    ~VertexBuffer();

	void Bind();
    void Unbind();

    const std::vector<std::tuple<ElementType::Type, int>>& GetLayout();
    void SetLayout(std::vector<std::tuple<ElementType::Type, int>> layout);
};