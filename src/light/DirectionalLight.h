#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

class DirectionalLight : public Publisher {
public:
    DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float intensity)
    : color(color), direction(direction), intensity(intensity) {}
    ~DirectionalLight() {}

    void SetIndex(int index);
    void SetColor(const glm::vec3& color);
    void SetDirection(const glm::vec3& direction);
    void SetIntensity(float intensity);

    const int GetIndex() { return index; }
    const glm::vec3& GetColor() { return color; }
    const glm::vec3& GetDirection() { return direction; }
    const float GetIntensity() { return intensity; }

private:
    int index;
    glm::vec3 color;
    glm::vec3 direction;
    float intensity;
};
