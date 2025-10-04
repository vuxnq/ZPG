#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "object/DrawableObject.h"

class Scene {
public:
    Scene() {}
    ~Scene() {}

    virtual void OnUpdate(float delta);
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);

private:
    std::vector<ref<DrawableObject>> drawableObjects;
};