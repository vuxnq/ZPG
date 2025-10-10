#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "core/Camera.h"

class Controller {
public:
    Controller(Camera& camera) : camera(camera) {}
    ~Controller() {}

    void Update(float delta);

private:
    Camera& camera;
    float speed = 2;
    float sensitivity = 100;
    float mouseSensitivity = 0.25f;

    float yaw = -90.0f;
    float pitch = 0.0f;

    double mouseLastPosition[2] = {0};

    void ProcessKeyboardInput(float delta);
    void ProcessMouseInput(float delta);
};
