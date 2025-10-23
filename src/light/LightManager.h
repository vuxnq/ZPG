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
        pointLights.push_back(light);
        light->AddSubscriber(this);
    }

    void OnNotify(const Event& event) override {
        if (event.type == EventType::PointLightSet) {
            auto light = (PointLight*)event.payload; // TODO: ziskat pozici ve vektoru a setuniform
        }
    }

    void Notify() override {}

private:
    std::vector<ref<PointLight>> pointLights;
};