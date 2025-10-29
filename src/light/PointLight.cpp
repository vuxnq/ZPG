#include "light/PointLight.h"

void PointLight::SetIndex(int index) {
    this->index = index;
    Notify(Event(EventType::PointLightSet, this));
}

void PointLight::SetColor(const glm::vec3& color) {
    this->color = color;
    Notify(Event(EventType::PointLightSet, this));
}

void PointLight::SetPosition(const glm::vec3& position) {
    this->position = position;
    Notify(Event(EventType::PointLightSet, this));
}

void PointLight::SetIntensity(int intensity) {
    this->intensity = intensity;
    Notify(Event(EventType::PointLightSet, this));
}
