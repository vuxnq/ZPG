#include "core/Camera.h"
#include "Application.h"

Camera::Camera() {
    ComputeViewMatrix();
    ComputerProjectionMatrix();
    Notify();
}


const glm::mat4& Camera::GetViewMatrix() {
    return viewMatrix;
}

const glm::mat4& Camera::GetProjMatrix() {
    return projectionMatrix;
}

void Camera::SetPosition(const glm::vec3& position) {
    this->position = position;
    ComputeViewMatrix();
    Notify();
}

void Camera::SetDirection(const glm::vec3& direction) {
    this->direction = direction;
    ComputeViewMatrix();
    Notify();
}

void Camera::SetAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    ComputerProjectionMatrix();
    Notify();
}

void Camera::Notify() {
    CameraPositionChangedPayload payload;
    payload.viewMatrix = viewMatrix;
    payload.projectionMatrix = projectionMatrix;
    Event event(EventType::CameraPositionChanged, &payload);

    for (auto& subscriber : subscribers) {
        subscriber->OnNotify(event);
    }
}

// TODO: move to controller
void Camera::Update(float delta) {
    float speed = 30;
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        position -= glm::vec3(0.0, 0.0, 0.1) * delta * speed;
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::vec3(0.1, 0.0, 0.0) * delta * speed;
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        position += glm::vec3(0.0, 0.0, 0.1) * delta * speed;
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::vec3(0.1, 0.0, 0.0) * delta * speed;
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += glm::vec3(0.0, 0.1, 0.0) * delta * speed;
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= glm::vec3(0.0, 0.1, 0.0) * delta * speed;
    }
    SetPosition(position);
}