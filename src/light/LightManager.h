#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Observer.h"
#include "light/PointLight.h"

class LightManager : public Publisher, public Subscriber {
public:
    LightManager() {}
    ~LightManager() {}

    void AddPointLight(const ref<PointLight> light) {
        light->AddSubscriber(this);
        light->SetIndex(pointLights.size());
        pointLights.push_back(light);
    }

    void OnNotify(const Event& event) override {
        if (event.type == EventType::PointLightSet) {
            Notify(event);
        }
    }

private:
    std::vector<ref<PointLight>> pointLights;
};