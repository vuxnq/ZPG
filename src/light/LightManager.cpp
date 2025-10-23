#include "light/LightManager.h"

void LightManager::AddPointLight(const ref<PointLight> light) {
    light->AddSubscriber(this);
    light->SetIndex(pointLights.size());
    pointLights.push_back(light);
}

void LightManager::OnNotify(const Event& event) {
    if (event.type == EventType::PointLightSet) {
        Notify(event);
    }
}