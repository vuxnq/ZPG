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
public:
    VertexBuffer(const float vertices[], size_t size, std::vector<std::tuple<ElementType::Type, int>> layout = {});
    ~VertexBuffer() {}

    void Bind();
    void Unbind();

    const std::vector<std::tuple<ElementType::Type, int>>& GetLayout() const;
    void SetLayout(std::vector<std::tuple<ElementType::Type, int>> layout);
    int GetStride() const;
    int GetSize() const { return size; }

private:
    GLuint id;
    int size;
    std::vector<std::tuple<ElementType::Type, int>> layout;
};
