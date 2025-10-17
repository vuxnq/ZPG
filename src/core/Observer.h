#pragma once
#include <glm/mat4x4.hpp>
#include <vector>
#include "core/Core.h"

enum EventType {
    CameraPositionChanged,
    PointLightSet,
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
    virtual void AddSubscriber(const ref<Subscriber>& subscriber) { subscribers.push_back(subscriber); }
    virtual void Notify() = 0;

protected:
    std::vector<ref<Subscriber>> subscribers;
};
