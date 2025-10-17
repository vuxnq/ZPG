#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

class PointLight : public Publisher {
public:
    PointLight(const glm::vec3& color, const glm::vec3& position) : color(color), position(position) {}
    ~PointLight() {}

    const glm::vec3& GetColor() { return color; }
    const glm::vec3& GetPosition() { return position; }

    void Notify() override {
        Event event(EventType::PointLightSet, this);

        for (auto& subscriber : subscribers) {
            subscriber->OnNotify(event);
        }
    }

private:
    glm::vec3 color;
    glm::vec3 position;
};
