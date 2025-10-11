#pragma once
#include <vector>
#include "core/Core.h"

enum EventType {
    CameraPositionChanged,
};

struct Payload {};

struct CameraPositionChangedPayload : public Payload {
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

struct Event {
    Event(EventType type, Payload* payload) : type(type), payload(payload) {}

    EventType type;
    Payload* payload;
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
