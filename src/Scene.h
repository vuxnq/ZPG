#pragma once
#include <GL/glew.h>
#include <vector>
#include "Core.h"
#include "DrawableObject.h"

class Scene {
public:
    Scene() {}
    ~Scene() {}

    void OnUpdate(float delta) {
        for (auto& drawableObject : drawableObjects) {
            drawableObject->Update(delta);
            drawableObject->Draw();
        }
    }
    void AddDrawableObject(const ref<DrawableObject>& drawableObject) {
        drawableObjects.push_back(drawableObject);
    }

private:
    std::vector<ref<DrawableObject>> drawableObjects;
};