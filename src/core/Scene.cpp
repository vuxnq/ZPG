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

void Scene::AddShaderProgram(const std::string& name, const ref<ShaderProgram> shaderProgram) {
    camera.AddSubscriber(shaderProgram.get());
    lightManager.AddSubscriber(shaderProgram.get());
    shaderProgramManager.AddShaderProgram(name, shaderProgram);

}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    drawableObjects.push_back(drawableObject);
}

void Scene::AddPointLight(const ref<PointLight>& light) {
    lightManager.AddPointLight(light);
}

void Scene::SetAspectRatio(float aspect) {
    camera.SetAspectRatio(aspect);
}
