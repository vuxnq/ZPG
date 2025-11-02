#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

class PointLight : public Publisher {
public:
    PointLight(const glm::vec3& color, const glm::vec3& position, float intensity)
    : color(color), position(position), intensity(intensity) {}
    ~PointLight() {}

    void SetIndex(int index);
    void SetColor(const glm::vec3& color);
    void SetPosition(const glm::vec3& position);
    void SetIntensity(float intensity);

    const int GetIndex() { return index; }
    const glm::vec3& GetColor() { return color; }
    const glm::vec3& GetPosition() { return position; }
    const float GetIntensity() { return intensity; }

private:
    int index;
    glm::vec3 color;
    glm::vec3 position;
    float intensity;
};
