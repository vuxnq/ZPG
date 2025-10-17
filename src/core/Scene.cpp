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

void Scene::AddPointLight(const ref<PointLight>& light) {
    pointLights.push_back(light);
}

void Scene::SetAspectRatio(float aspect) {
    camera.SetAspectRatio(aspect);
}

void Scene::SetPointLights() {
    for (int i = 0; i < shaderPrograms.size(); i++) {
        for (int j = 0; j < pointLights.size(); j++) {
            shaderPrograms[i]->Use();
            shaderPrograms[i]->SetUniform("pointLights[" + std::to_string(j) + "].color", pointLights[j]->GetColor());
            shaderPrograms[i]->SetUniform("pointLights[" + std::to_string(j) + "].position", pointLights[j]->GetPosition());
        }
    }
}
