#include "light/DirectionalLight.h"

void DirectionalLight::SetIndex(int index) {
    this->index = index;
    Notify(Event(EventType::DirectionalLightSet, this));
}

void DirectionalLight::SetColor(const glm::vec3& color) {
    this->color = color;
    Notify(Event(EventType::DirectionalLightSet, this));
}

void DirectionalLight::SetDirection(const glm::vec3& direction) {
    this->direction = direction;
    Notify(Event(EventType::DirectionalLightSet, this));
}

void DirectionalLight::SetIntensity(float intensity) {
    this->intensity = intensity;
    Notify(Event(EventType::DirectionalLightSet, this));
}
