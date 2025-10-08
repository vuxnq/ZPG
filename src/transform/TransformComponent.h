#pragma once
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class TransformComponent {
public:
    virtual ~TransformComponent() {}
    virtual glm::mat4 GetMatrix() = 0;
    virtual void Update(float delta) {}
};
