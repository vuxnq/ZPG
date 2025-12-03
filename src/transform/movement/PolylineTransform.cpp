#include "transform/movement/PolylineTransform.h"
#include <glm/gtc/matrix_transform.hpp>

PolylineTransform::PolylineTransform(const std::vector<glm::vec3>& points, const float duration, const bool rotate, const bool loop)
: MovementTransformComponent(duration, rotate, loop), points(points) {}

glm::mat4 PolylineTransform::GetMatrix() {
    if (points.empty()) return glm::mat4(1.0f);
    if (points.size() == 1) return glm::translate(glm::mat4(1.0f), points[0]);

    float time = elapsed / duration;

    int segCount = points.size() - 1;
    float scaled = time * segCount;

    int index = std::floor(scaled);
    index = std::min(index, segCount - 1);

    float localTime = scaled - index;

    glm::vec3 a = points[index];
    glm::vec3 b = points[index + 1];
    glm::vec3 pos = (1 - localTime) * a + localTime * b;

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    if (rotate) {
        glm::vec3 worldUp = glm::vec3(0, 1, 0);
        glm::vec3 front = glm::normalize(b - a);

        glm::vec3 right = glm::cross(front, worldUp);
        glm::vec3 up = glm::cross(right, front);

        rotationMatrix = glm::mat4(
            glm::vec4(right,   0),
            glm::vec4(up,      0),
            glm::vec4(front,   0),
            glm::vec4(0, 0, 0, 1)
        );
        rotationMatrix = glm::inverse(glm::lookAt(glm::vec3(0), -front, up));
    }

    return glm::translate(glm::mat4(1.0f), pos) * rotationMatrix;
}
