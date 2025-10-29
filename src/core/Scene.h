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
#include "light/SpotLight.h"

class Scene {
public:
    Scene() : controller(camera) {}
    ~Scene() {}

    virtual void OnUpdate(float delta);

    void AddShaderProgram(const std::string& name, const ref<ShaderProgram> shaderProgram);
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);

    void SetAmbientLight(const glm::vec3& color);
    void AddLight(const ref<DirectionalLight>& light);
    void AddLight(const ref<PointLight>& light);
    void AddLight(const ref<SpotLight>& light);

    void SetAspectRatio(float aspect);

private:
    std::vector<ref<DrawableObject>> drawableObjects;

protected:
    Camera camera;
    Controller controller;
    ShaderProgramManager shaderProgramManager;
    LightManager lightManager;
};