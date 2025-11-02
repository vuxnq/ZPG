#pragma once
#include <GL/glew.h>
#include "light/SpotLight.h"
#include "core/Camera.h"

class Flashlight : public SpotLight, public Subscriber {
public:
    Flashlight(const glm::vec3& color, const LightAttenuation& attenuation) : SpotLight(color, glm::vec3(0.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, -1.f), attenuation), flashlightIntensity(attenuation.intensity) {}
    ~Flashlight() {}

    // TODO: refactor flashlight and move to .cpp
    void SetFlashlightIntensity(float intensity) {
        this->flashlightIntensity = intensity;
    }
    void SetIntensity(float intensity) {
        auto a = GetAttenuation();
        SetAttenuation({
            .intensity = intensity,
            .constant = a.constant,
            .linear = a.linear,
            .quadratic = a.quadratic,
        });
    }

    float GetFlashlightIntensity() { return flashlightIntensity; }

    void OnNotify(const Event& event) override {
        if (event.type == EventType::CameraPositionChanged) {
            auto camera = (Camera*)event.payload;
            SetPosition(camera->GetPosition());
            SetDirection(camera->GetDirection());
        }
    }

private:
    float flashlightIntensity; // TODO: rename this shit
};