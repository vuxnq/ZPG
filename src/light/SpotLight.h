#pragma once
#include "light/Light.h"

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction, const LightAttenuation& attenuation)
    : Light(color, attenuation), position(position), direction(direction) {}
    ~SpotLight() {}

    void SetPosition(const glm::vec3& position);
    void SetDirection(const glm::vec3& direction);

    const glm::vec3& GetPosition() { return position; }
    const glm::vec3& GetDirection() { return direction; }

    EventType GetEventType() override { return EventType::SpotLightSet; }

private:
    glm::vec3 position;
    glm::vec3 direction;
};
