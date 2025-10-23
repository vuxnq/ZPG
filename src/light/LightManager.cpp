#include "light/LightManager.h"

void LightManager::AddPointLight(const ref<PointLight> light) {
    light->AddSubscriber(this);
    light->SetIndex(pointLights.size());
    pointLights.push_back(light);
    Notify(Event(EventType::PointLightCountSet, (void*)pointLights.size()));
}

void LightManager::OnNotify(const Event& event) {
    if (event.type == EventType::PointLightSet) {
        Notify(event);
    }
}
