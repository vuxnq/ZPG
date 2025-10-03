#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Model.h"
#include "DrawableObject.h"
#include "SceneManager.h"

class Application {
public:
    Application();
    ~Application() {}

    void Init();
    void SetUpCallbacks();
    void OnCreate();
    void Run();
    void Shutdown();

private:
    GLFWwindow* window;
    ref<ShaderProgram> shaderProgram;
    SceneManager sceneManager;
};