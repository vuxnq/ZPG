#include "core/Scene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "core/Application.h"

void Scene::OnUpdate(float delta) {
    controller.Update(delta);

    for (auto& drawableObject : drawableObjects) {
        drawableObject->Update(delta);
    }
}

void Scene::OnDraw() {
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_STENCIL_BUFFER_BIT); // TODO

    for (auto& drawableObject : drawableObjects) {
        glStencilFunc(GL_ALWAYS, (GLuint)drawableObject->GetIndex(), 0xFF);
        drawableObject->Draw();
    }
}

void Scene::AddShaderProgram(const std::string& name, const ref<ShaderProgram> shaderProgram) {
    camera.AddSubscriber(shaderProgram.get());
    lightManager.AddSubscriber(shaderProgram.get());
    shaderProgramManager.AddShaderProgram(name, shaderProgram);
}

void Scene::AddDrawableObject(const ref<DrawableObject>& drawableObject) {
    int index = stencil++ % 255;
    drawableObject->SetIndex(index);
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
        if (drawableObjects[i]->GetIndex() == index) {
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

glm::vec3 Scene::ScreenToWorld(float x, float y, float depth) {
    auto app = Application::Get();
    int windowWidth = app->GetResolution().x;
    int windowHeight = app->GetResolution().y;
    float invertedY = windowHeight - y;

    glm::vec3 screenPos = glm::vec3(x, invertedY, depth);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjMatrix();
    glm::vec4 viewPort = glm::vec4(0, 0, windowWidth, windowHeight);
    glm::vec3 pos = glm::unProject(screenPos, view, projection, viewPort);
    return pos;
}
