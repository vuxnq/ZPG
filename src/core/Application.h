#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core/Core.h"
#include "core/ShaderProgram.h"
#include "core/SceneManager.h"

class Application {
public:
    Application();
    ~Application() {}

    void Init();
    void SetUpCallbacks();
    void OnCreate();
    void Run();
    void Shutdown();

    static Application* Get() { return s_application; }
    GLFWwindow* GetWindow() { return window; }

private:
    GLFWwindow* window;
    SceneManager sceneManager;

    void OnKey(int key, int action);

    inline static Application* s_application = nullptr;
};