#include "light/PointLight.h"

void PointLight::SetPosition(const glm::vec3& position) {
    this->position = position;
    Notify();
}

void PointLight::SetColor(const glm::vec3& color) {
    this->color = color;
    Notify();
}

void PointLight::Notify() {
    Event event(EventType::PointLightSet, this);

    for (auto& subscriber : subscribers) {
        subscriber->OnNotify(event);
    }
}
