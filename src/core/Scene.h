#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Camera.h"
#include "core/Controller.h"
#include "shader/ShaderProgramManager.h"
#include "light/LightManager.h"
#include "object/DrawableObject.h"
#include "light/PointLight.h"

class Scene {
public:
    Scene() : controller(camera) {}
    ~Scene() {}

    virtual void OnUpdate(float delta); // TODO: add renderer class mb drawableobj by se nemel sam kreslit
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);
    void AddPointLight(const ref<PointLight>& light);

    void SetAspectRatio(float aspect);

private:
    std::vector<ref<DrawableObject>> drawableObjects;

protected:
    Camera camera;
    Controller controller;
    ShaderProgramManager shaderProgramManager;
    LightManager lightManager;
};