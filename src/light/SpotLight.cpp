#include "light/SpotLight.h"

void SpotLight::SetPosition(const glm::vec3& position) {
    this->position = position;
    Notify(Event(EventType::SpotLightSet, this));
}

void SpotLight::SetDirection(const glm::vec3& direction) {
    this->direction = direction;
    Notify(Event(EventType::SpotLightSet, this));
}
