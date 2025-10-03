#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

class Application {
public:
    Application();
    ~Application() {}

    void Init();
    void SetUpCallbacks();
    void CreateModels();
    void Run();
    void Shutdown();

private:
    GLFWwindow* window;
    ShaderProgram* shaderProgram;

    // temporary solution
    VertexBuffer* vb1;
    VertexBuffer* vb2;
    VertexBuffer* vb3;

    VertexArray* va1;
    VertexArray* va2;
    VertexArray* va3;
};