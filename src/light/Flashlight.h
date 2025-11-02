#pragma once
#include <GL/glew.h>
#include "light/SpotLight.h"
#include "core/Camera.h"

class Flashlight : public SpotLight, public Subscriber {
public:
    Flashlight(const glm::vec3& color, const LightAttenuation& attenuation)
    : SpotLight(color, glm::vec3(0.f, 0.f, 0.f),  glm::vec3(0.f, 0.f, -1.f), attenuation), attenuation(attenuation) {}
    ~Flashlight() {}

    void SetFlashlightAttenuation(const LightAttenuation& attenuation);

    const LightAttenuation& GetFlashlightAttenuation() { return attenuation; }

    void OnNotify(const Event& event) override;

private:
    LightAttenuation attenuation;
};
