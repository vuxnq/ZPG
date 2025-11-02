#pragma once
#include "light/Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& color, const glm::vec3& position, const LightAttenuation& attenuation)
    : Light(color, attenuation), position(position) {}
    ~PointLight() {}

    void SetPosition(const glm::vec3& position);
    const glm::vec3& GetPosition() { return position; }

    EventType GetEventType() override { return EventType::PointLightSet; }

private:
    glm::vec3 position;
};
