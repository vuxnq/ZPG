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
    Camera();
    ~Camera() {}

    const glm::mat4& GetViewMatrix();
    const glm::mat4& GetProjMatrix();

    void SetPosition(const glm::vec3& position);
    void SetDirection(const glm::vec3& direction);
    void SetAspectRatio(float aspectRatio);

    void Notify() override;

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