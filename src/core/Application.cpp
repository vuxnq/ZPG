#include "core/Application.h"

// glew, glfw
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// standard C++ headers
#include <iostream>
#include <fstream>
#include <sstream>

#include "core/Callbacks.h"
#include "shader/ShaderProgram.h"
#include "object/VertexBuffer.h"
#include "object/VertexArray.h"
#include "object/Model.h"
#include "object/DrawableObject.h"
#include "transform/Transformation.h"

#include "scenes/Cv10Scenes.h"
#include "scenes/Cv11Scenes.h"

Application::Application() {
    if (s_application != nullptr) {
        fprintf(stderr, "Application already instantiated\n");
        exit(EXIT_FAILURE);
    }
    s_application = this;
}

void Application::Init() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    // depth comparisons and update the depth buffer
    glEnable(GL_DEPTH_TEST);

    // stencil
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // // alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // get version info
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %d.%d.%d\n", major, minor, revision);
}

void Application::SetUpCallbacks() {
    // glfwSetKeyCallback(window, key_callback);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        Application::Get()->OnKey(key, action);
    });
    // glfwSetCursorPosCallback(window, cursor_callback);
    // glfwSetMouseButtonCallback(window, button_callback);
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
        Application::Get()->OnMouseButton(button, action, mods);
    });
    // glfwSetWindowFocusCallback(window, window_focus_callback);
    // glfwSetWindowIconifyCallback(window, window_iconify_callback);
    // glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);
        Application::Get()->OnWindowResize(width, height);
    });
}

void Application::OnKey(int key, int action) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_1:
                sceneManager.SetActiveScene("scene10.1");
                sceneManager.GetActiveScene()->SetAspectRatio(windowWidth / (float)windowHeight);
                break;
            case GLFW_KEY_2:
                sceneManager.SetActiveScene("scene10.2");
                sceneManager.GetActiveScene()->SetAspectRatio(windowWidth / (float)windowHeight);
                break;
            case GLFW_KEY_3:
                sceneManager.SetActiveScene("scene10.3");
                sceneManager.GetActiveScene()->SetAspectRatio(windowWidth / (float)windowHeight);
                break;
            case GLFW_KEY_4:
                sceneManager.SetActiveScene("scene11.1");
                sceneManager.GetActiveScene()->SetAspectRatio(windowWidth / (float)windowHeight);
                break;
            default:
                break;
        }
    }
    sceneManager.GetActiveScene()->OnKey(key, action);
}

void Application::OnWindowResize(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    sceneManager.GetActiveScene()->SetAspectRatio(windowWidth / (float)windowHeight);
}

void Application::OnMouseButton(int button, int action, int mods) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    sceneManager.GetActiveScene()->OnMouseButton(button, action, mods, x, y);
}

void Application::ReadPixel(int x, int y, GLbyte* color, GLfloat& depth, GLuint& index) {
    GLint invertedY = windowHeight - y;
    glReadPixels(x, invertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, invertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, invertedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
}

void Application::OnCreate() {
    sceneManager.AddScene("scene10.1", make_ref(new Cv10Scene1()));
    sceneManager.AddScene("scene10.2", make_ref(new Cv10Scene2()));
    sceneManager.AddScene("scene10.3", make_ref(new Cv10Scene3()));
    sceneManager.AddScene("scene11.1", make_ref(new Cv11Scene1()));
}

void Application::Run() {
    float lastTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float delta = currentTime - lastTime;
        lastTime = currentTime;

        sceneManager.GetActiveScene()->OnUpdate(delta);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        sceneManager.GetActiveScene()->DrawSkybox();

        glClear(GL_DEPTH_BUFFER_BIT);

        sceneManager.GetActiveScene()->OnDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::Shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
