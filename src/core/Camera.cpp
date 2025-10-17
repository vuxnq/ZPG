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
    Event event(EventType::CameraPositionChanged, this);

    for (auto& subscriber : subscribers) {
        subscriber->OnNotify(event);
    }
}

void Camera::ComputeViewMatrix() {
    viewMatrix = glm::lookAt(position, position + direction, up);
}

void Camera::ComputerProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}
