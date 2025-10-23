#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Observer.h"
#include "object/PointLight.h"

class LightManager : Subscriber {
public:
    LightManager() {}
    ~LightManager() {}

    void AddPointLight(const ref<PointLight> light);

    void OnNotify(const Event& event) override {
        auto light = (PointLight*)event.payload; // TODO: ziskat pozici ve vektoru a setuniform
    }

private:
    std::vector<ref<PointLight>> pointLights;
};