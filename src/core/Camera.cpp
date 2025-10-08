#include "core/Camera.h"
#include "Application.h"

void Camera::Update(float delta) {
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        position += glm::vec3(0.0, 0.0, 0.1);
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        position += glm::vec3(0.1, 0.0, 0.0);
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        position -= glm::vec3(0.0, 0.0, 0.1);
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        position -= glm::vec3(0.1, 0.0, 0.0);
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += glm::vec3(0.0, 0.1, 0.0);
    }
    if (glfwGetKey(Application::Get()->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= glm::vec3(0.0, 0.1, 0.0);
    }
    SetPosition(position);
}