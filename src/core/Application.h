#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core/Core.h"
#include "shader/ShaderProgram.h"
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
    inline static Application* s_application = nullptr;

    GLFWwindow* window;
    SceneManager sceneManager;

    int windowWidth = 640;
    int windowHeight = 480;

    void OnKey(int key, int action);
    void OnWindowResize(int width, int height);
};
