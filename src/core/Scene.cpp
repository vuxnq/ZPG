#include "core/Scene.h"
#include <iostream>
#include "Scene.h"

void Scene::OnUpdate(float delta) {
    controller.Update(delta);

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
        drawableObject->Draw();
    }
}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    drawableObjects.push_back(drawableObject);
}

void Scene::SetAspectRatio(float aspect) {
    camera.SetAspectRatio(aspect);
}
