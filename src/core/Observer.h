#pragma once
#include <glm/mat4x4.hpp>
#include <vector>
#include "core/Core.h"

enum EventType {
    CameraPositionChanged,
    AmbientLightSet,
    PointLightSet,
    SpotLightSet,
    PointLightCountSet,
    SpotLightCountSet,
};

struct Event {
    Event(EventType type, void* payload) : type(type), payload(payload) {}

    EventType type;
    void* payload;
};

class Subscriber {
public:
    virtual ~Subscriber() {}
    virtual void OnNotify(const Event& event) = 0;
};

class Publisher {
public:
    virtual ~Publisher() {}
    virtual void AddSubscriber(Subscriber* subscriber) { subscribers.push_back(subscriber); }
    virtual void Notify(Event event) { for (auto& subscriber : subscribers) subscriber->OnNotify(event); }

protected:
    std::vector<Subscriber*> subscribers;
};
