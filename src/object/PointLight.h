#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

class PointLight : public Publisher {
public:
    PointLight(const glm::vec3& color, const glm::vec3& position) : color(color), position(position) {}
    ~PointLight() {}

    void SetPosition(const glm::vec3& position);
    void SetColor(const glm::vec3& color);

    const glm::vec3& GetColor() { return color; }
    const glm::vec3& GetPosition() { return position; }

    void Notify() override;

private:
    glm::vec3 color;
    glm::vec3 position;
};
