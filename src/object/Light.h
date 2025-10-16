#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

class PointLight : public Publisher {
public:
    PointLight(const glm::vec3& color, const glm::vec3& position) : color(color), position(position) {}
    ~PointLight() {}

    void Notify() override {
        PointLightSetPayload payload;
        payload.color = color;
        payload.position = position;
        Event event(EventType::PointLightSet, &payload);

        for (auto& subscriber : subscribers) {
            subscriber->OnNotify(event);
        }
    }

private:
    glm::vec3 color;
    glm::vec3 position;
};
