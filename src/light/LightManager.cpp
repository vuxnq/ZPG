#include "light/LightManager.h"

void LightManager::SetAmbientLight(const glm::vec3& color) {
    Notify(Event(EventType::AmbientLightSet, (void*)&color));
}

void LightManager::AddLight(const ref<DirectionalLight>& light) {
    light->AddSubscriber(this);
    light->SetIndex(directionalLights.size());
    directionalLights.push_back(light);
    Notify(Event(EventType::DirectionalLightCountSet, (void*)directionalLights.size()));
}

void LightManager::AddLight(const ref<PointLight>& light) {
    light->AddSubscriber(this);
    light->SetIndex(pointLights.size());
    pointLights.push_back(light);
    Notify(Event(EventType::PointLightCountSet, (void*)pointLights.size()));
}

void LightManager::AddLight(const ref<SpotLight>& light) {
    light->AddSubscriber(this);
    light->SetIndex(spotLights.size());
    spotLights.push_back(light);
    Notify(Event(EventType::SpotLightCountSet, (void*)spotLights.size()));
}

void LightManager::OnNotify(const Event& event) {
    if (event.type == EventType::DirectionalLightSet) Notify(event);
    else if (event.type == EventType::PointLightSet) Notify(event);
    else if (event.type == EventType::SpotLightSet) Notify(event);
}
