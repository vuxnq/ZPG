#include "core/Scene.h"
#include <iostream>
#include "core/Application.h"

void Scene::OnUpdate(float delta) {
    controller.Update(delta);

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
    }
}

void Scene::OnDraw() {
    for (auto& drawableObject : drawableObjects) {
        glStencilFunc(GL_ALWAYS, (GLuint)drawableObject->GetIndex(), 0xFF);
        drawableObject->Draw();
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
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

void Scene::RemoveDrawableObject(const ref<DrawableObject>& drawableObject) {
    for (int i = 0; i < drawableObjects.size(); i++) {
        if (drawableObjects[i] == drawableObject) {
            drawableObjects.erase(drawableObjects.begin() + i);
            return;
        }
    }
}

void Scene::RemoveDrawableObject(int index) {
    for (int i = 0; i < drawableObjects.size(); i++) {
        if (drawableObjects[i]->GetIndex() % 0xFF == index) {
            drawableObjects.erase(drawableObjects.begin() + i);
            return;
        }
    }
}

void Scene::SetAmbientLight(const glm::vec3& color) {
    lightManager.SetAmbientLight(color);
}

void Scene::AddLight(const ref<DirectionalLight>& light) {
    lightManager.AddLight(light);
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

void Scene::SetSkybox(const SkyboxFaces& faces) {
    skybox.SetSkybox(faces);
    AddShaderProgram("skyboxShader", skybox.GetShaderProgram());
}

void Scene::DrawSkybox() {
    skybox.Draw();
}
