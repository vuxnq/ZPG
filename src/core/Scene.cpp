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
    for (auto& shaderProgram : shaderProgramManager.GetShaderPrograms()) { // TODO: uniformbuffer
        for (int j = 0; j < pointLights.size(); j++) {
            shaderProgram.second->Use();
            std::string base = "pointLights[" + std::to_string(j) + "]";
            shaderProgram.second->SetUniform(base + ".color", pointLights[j]->GetColor());
            shaderProgram.second->SetUniform(base + ".position", pointLights[j]->GetPosition());
            shaderProgram.second->SetUniform(base + ".intensity", pointLights[j]->GetIntensity());
        }
    }
}
