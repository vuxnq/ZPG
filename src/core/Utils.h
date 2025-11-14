#pragma once
#include <glm/glm.hpp>

class Camera;

namespace utils {
    glm::vec3 ScreenToWorld(float x, float y, float depth, const Camera& camera);
}
