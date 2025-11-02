#include "light/PointLight.h"

void PointLight::SetPosition(const glm::vec3& position) {
    this->position = position;
    Notify(Event(EventType::PointLightSet, this));
}
