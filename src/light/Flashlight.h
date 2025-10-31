#pragma once
#include <GL/glew.h>
#include "light/SpotLight.h"
#include "core/Camera.h"

class Flashlight : public SpotLight, public Subscriber {
public:
    Flashlight(const glm::vec3& color, int intensity) : SpotLight(color, glm::vec3(0.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, -1.f), intensity), flashlightIntensity(intensity) {}

    void SetFlashlightIntensity(int intensity) {
        this->flashlightIntensity = intensity;
    }

    int GetFlashlightIntensity() { return flashlightIntensity; }

    void OnNotify(const Event& event) override {
        if (event.type == EventType::CameraPositionChanged) {
            auto camera = (Camera*)event.payload;
            SetPosition(camera->GetPosition());
            SetDirection(camera->GetDirection());
        }
    }

private:
    int flashlightIntensity; // TODO: rename this shit
};