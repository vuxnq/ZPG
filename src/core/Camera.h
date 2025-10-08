#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Core.h"
#include "core/Observer.h"
#include <GLFW/glfw3.h>

class Camera : public Publisher {
public:
    Camera() {
        ComputeViewMatrix();
        ComputerProjectionMatrix();
        Notify();
    }
    ~Camera() {}

    const glm::mat4& GetViewMatrix() {
        return viewMatrix;
    }

    const glm::mat4& GetProjMatrix() {
        return projectionMatrix;
    }

    void SetPosition(const glm::vec3& position) {
        this->position = position;
        ComputeViewMatrix();
        Notify();
    }

    const glm::vec3& GetPosition() const {
        return position;
    }

    void SetDirection(const glm::vec3& direction) {
        this->direction = direction;
        ComputeViewMatrix();
        Notify();
    }

    void SetAspectRatio(float aspectRatio) {
        this->aspectRatio = aspectRatio;
        ComputerProjectionMatrix();
        Notify();
    }

    void Notify() override {
        CameraPositionChangedPayload payload;
        payload.viewMatrix = viewMatrix;
        payload.projectionMatrix = projectionMatrix;
        Event event(EventType::CameraPositionChanged, &payload);

        for (auto& subscriber : subscribers) {
            subscriber->OnNotify(event);
        }
    }

    void Update(float delta);

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float aspectRatio = 1.5f;
    float fov = 75.0f;

    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 direction = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);

    void ComputeViewMatrix() {
        viewMatrix = glm::lookAt(position, position + direction, up);
    }
    void ComputerProjectionMatrix() {
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
    }
};