#include "core/Utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/Application.h"

glm::vec3 utils::ScreenToWorld(float x, float y, float depth, const Camera& camera) {
    auto app = Application::Get();
    int windowWidth = app->GetResolution().x;
    int windowHeight = app->GetResolution().y;
    float invertedY = windowHeight - y;

    glm::vec3 screenPos = glm::vec3(x, invertedY, depth);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjMatrix();
    glm::vec4 viewPort = glm::vec4(0, 0, windowWidth, windowHeight);
    glm::vec3 pos = glm::unProject(screenPos, view, projection, viewPort);
    return pos;
}
