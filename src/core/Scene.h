#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Camera.h"
#include "core/Controller.h"
#include "object/DrawableObject.h"
#include "object/Light.h"

class Scene {
public:
    Scene() : controller(camera) {}
    ~Scene() {}

    virtual void OnUpdate(float delta); // TODO: add renderer class mb drawableobj by se nemel sam kreslit
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);
    void AddPointLight(const ref<PointLight>& light);

    void SetAspectRatio(float aspect);

    void SetPointLights(); // TODO: this should be in renderer

private:
    std::vector<ref<DrawableObject>> drawableObjects;
    std::vector<ref<PointLight>> pointLights;

protected:
    Camera camera;
    Controller controller;
    std::vector<ref<ShaderProgram>> shaderPrograms; // TODO: Asi nejako takto asi jako map stejne jako scenemanager asi to predelat na shaderprogrammanager
};