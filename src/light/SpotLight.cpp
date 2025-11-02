#include "light/SpotLight.h"

void SpotLight::SetIndex(int index) {
    this->index = index;
    Notify(Event(EventType::SpotLightSet, this));
}

void SpotLight::SetColor(const glm::vec3& color) {
    this->color = color;
    Notify(Event(EventType::SpotLightSet, this));
}

void SpotLight::SetPosition(const glm::vec3& position) {
    this->position = position;
    Notify(Event(EventType::SpotLightSet, this));
}

void SpotLight::SetDirection(const glm::vec3& direction) {
    this->direction = direction;
    Notify(Event(EventType::SpotLightSet, this));
}

void SpotLight::SetIntensity(float intensity) {
    this->intensity = intensity;
    Notify(Event(EventType::SpotLightSet, this));
}
