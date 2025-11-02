#pragma once
#include <GL/glew.h>
#include "light/SpotLight.h"
#include "core/Camera.h"

class Flashlight : public SpotLight, public Subscriber {
public:
    Flashlight(const glm::vec3& color, float intensity) : SpotLight(color, glm::vec3(0.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, -1.f), intensity), flashlightIntensity(intensity) {}
    ~Flashlight() {}

    void SetFlashlightIntensity(float intensity) {
        this->flashlightIntensity = intensity;
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