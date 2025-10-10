#include "core/Controller.h"
#include "core/Application.h"
#include <iostream>

void Controller::Update(float delta) {
    ProcessKeyboardInput(delta);
    ProcessMouseInput(delta);
}

void Controller::ProcessKeyboardInput(float delta) {
    GLFWwindow* window = Application::Get()->GetWindow();

    glm::vec3 position = camera.GetPosition();
    glm::vec3 direction = camera.GetDirection();

    glm::vec3 up = camera.GetUp();
    glm::vec3 right = glm::normalize(glm::cross(direction, up));
    glm::vec3 forward = glm::normalize(glm::cross(up, right));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += forward * delta * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * delta * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= forward * delta * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * delta * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += up * delta * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= up * delta * speed;
    }

    camera.SetPosition(position);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        pitch += sensitivity * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        yaw -= sensitivity * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        pitch -= sensitivity * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        yaw += sensitivity * delta;
    }

    pitch = glm::clamp(pitch, -89.0f, 89.0f);


    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    camera.SetDirection(glm::normalize(dir));
}

void Controller::ProcessMouseInput(float delta) {
    GLFWwindow* window = Application::Get()->GetWindow();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        std::cout << "pressed"<< std::endl;

        double mouseCurrentPosition[2];
        double offset[2];
        glfwGetCursorPos(window, &mouseCurrentPosition[0], &mouseCurrentPosition[1]);
        offset[0] = (mouseCurrentPosition[0] - mouseLastPosition[0]) * mouseSensitivity;
        offset[1] = (mouseLastPosition[1] - mouseCurrentPosition[1]) * mouseSensitivity;
        std::cout << "xoffset: " << offset[0] << " yoffset: " << offset[1] << std::endl;

        yaw += offset[0];
        pitch += offset[1];

        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        glm::vec3 dir;
        dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        dir.y = sin(glm::radians(pitch));
        dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        camera.SetDirection(glm::normalize(dir));

        mouseLastPosition[0] = mouseCurrentPosition[0];
        mouseLastPosition[1] = mouseCurrentPosition[1];
    } else {
        glfwGetCursorPos(window, &mouseLastPosition[0], &mouseLastPosition[1]);
        std::cout << "x: " << mouseLastPosition[0] << " y:" << mouseLastPosition[1] << std::endl;
    }
}
