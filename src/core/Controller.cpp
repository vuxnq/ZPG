#include "core/Controller.h"
#include "core/Application.h"

void Controller::Update(float delta) {
    ProcessKeyboardInput(delta);
    ProcessMouseInput();
}

void Controller::ProcessKeyboardInput(float delta) {
    GLFWwindow* window = Application::Get()->GetWindow();

    glm::vec3 position = camera.GetPosition();
    glm::vec3 oldPosition = position;
    glm::vec3 direction = camera.GetDirection();

    glm::vec3 up = camera.GetUp();
    glm::vec3 right = glm::normalize(glm::cross(direction, up));
    glm::vec3 forward = glm::normalize(glm::cross(up, right));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += forward * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= right * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= forward * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += right * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) position += up * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position -= up * delta * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed = highSpeed; else speed = normalSpeed;

    if (position != oldPosition) {
        camera.SetPosition(position);
    }

    float oldYaw = yaw;
    float oldPitch = pitch;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) pitch += rotationSpeed * delta;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) yaw -= rotationSpeed * delta;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) pitch -= rotationSpeed * delta;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) yaw += rotationSpeed * delta;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    if (yaw != oldYaw || pitch != oldPitch) {
        camera.SetDirection(ComputeDirection(yaw, pitch));
    }
}

void Controller::ProcessMouseInput() {
    GLFWwindow* window = Application::Get()->GetWindow();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        double mouseCurrentPosition[2];
        double offset[2];
        glfwGetCursorPos(window, &mouseCurrentPosition[0], &mouseCurrentPosition[1]);
        offset[0] = (mouseCurrentPosition[0] - mouseLastPosition[0]) * mouseSensitivity;
        offset[1] = (mouseCurrentPosition[1] - mouseLastPosition[1]) * mouseSensitivity;

        yaw += offset[0];
        pitch -= offset[1];

        pitch = glm::clamp(pitch, -89.0f, 89.0f);

        camera.SetDirection(ComputeDirection(yaw, pitch));

        mouseLastPosition[0] = mouseCurrentPosition[0];
        mouseLastPosition[1] = mouseCurrentPosition[1];
    } else {
        glfwGetCursorPos(window, &mouseLastPosition[0], &mouseLastPosition[1]);
    }
}

glm::vec3 Controller::ComputeDirection(float yawDeg, float pitchDeg) const {
    glm::vec3 dir;
    dir.x = cos(glm::radians(yawDeg)) * cos(glm::radians(pitchDeg));
    dir.y = sin(glm::radians(pitchDeg));
    dir.z = sin(glm::radians(yawDeg)) * cos(glm::radians(pitchDeg));
    return glm::normalize(dir);
}
