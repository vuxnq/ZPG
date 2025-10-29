#include "core/Scene.h"
#include <iostream>

void Scene::OnUpdate(float delta) {
    controller.Update(delta);

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
        drawableObject->Draw();
    }
}

void Scene::AddShaderProgram(const std::string& name, const ref<ShaderProgram> shaderProgram) {
    camera.AddSubscriber(shaderProgram.get());
    lightManager.AddSubscriber(shaderProgram.get());
    shaderProgramManager.AddShaderProgram(name, shaderProgram);

}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    drawableObjects.push_back(drawableObject);
}

void Scene::SetAmbientLight(const glm::vec3& color) {
    lightManager.SetAmbientLight(color);
}

void Scene::AddLight(const ref<PointLight>& light) {
    lightManager.AddLight(light);
}

void Scene::AddLight(const ref<SpotLight>& light) {
    lightManager.AddLight(light);
}

void Scene::SetAspectRatio(float aspect) {
    camera.SetAspectRatio(aspect);
}
