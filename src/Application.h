#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

class Application {
private:
    GLFWwindow* window;
    ShaderProgram* shaderProgram;
    ShaderProgram* shaderProgram2;

    // temporary solution
    VertexBuffer* vb1;
    VertexBuffer* vb2;

    VertexArray* va1;
    VertexArray* va2;

public:
    Application();
    ~Application() {}

    void Init();
    void SetUpCallbacks();
    void CreateModels();
    void Run();
    void Shutdown();
};