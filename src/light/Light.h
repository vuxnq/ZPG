#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "core/Core.h"
#include "core/Observer.h"

struct LightAttenuation {
    float intensity = 1.0;
    float constant = 1.0;
    float linear = 1.0;
    float quadratic = 1.0;
};

class Light : public Publisher {
public:
    Light(const glm::vec3& color, const LightAttenuation& attenuation) : color(color), attenuation(attenuation) {}
    ~Light() {}

    void SetIndex(int index) {
        this->index = index;
        Notify(Event(GetEventType(), this));
    }
    void SetColor(const glm::vec3& color) {
        this->color = color;
        Notify(Event(GetEventType(), this));
    }
    void SetAttenuation(const LightAttenuation& attenuation) {
        this->attenuation = attenuation;
        Notify(Event(GetEventType(), this));
    }

    const int GetIndex() { return index; }
    const glm::vec3& GetColor() { return color; }
    const LightAttenuation GetAttenuation() { return attenuation; }

    virtual EventType GetEventType() = 0;

private:
    int index;
    glm::vec3 color;
    LightAttenuation attenuation;
};