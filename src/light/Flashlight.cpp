#include "light/Flashlight.h"

void Flashlight::SetFlashlightAttenuation(const LightAttenuation& attenuation) {
    this->attenuation = attenuation;
    SetAttenuation(attenuation);
}

void Flashlight::OnNotify(const Event& event) {
    if (event.type == EventType::CameraPositionChanged) {
        auto camera = (Camera*)event.payload;
        SetPosition(camera->GetPosition());
        SetDirection(camera->GetDirection());
    }
}
