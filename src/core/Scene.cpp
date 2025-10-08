#include "core/Scene.h"
#include <iostream>

void Scene::OnUpdate(float delta) {
    camera.Update(delta); // TODO: added without thinking mb refactor

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
        drawableObject->Draw();
    }
}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    drawableObjects.push_back(drawableObject);
}