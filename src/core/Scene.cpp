#include "core/Scene.h"
#include <iostream>

void Scene::OnUpdate(float delta) {
    camera.Update(delta);

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
        drawableObject->Draw();
    }

    auto p = camera.GetPosition();
    std::cout << p.x << " " << p.y << " " << p.z << std::endl;
}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    drawableObjects.push_back(drawableObject);
}