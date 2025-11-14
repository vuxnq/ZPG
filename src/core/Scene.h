#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include "core/Core.h"
#include "core/Camera.h"
#include "core/Controller.h"
#include "shader/ShaderProgramManager.h"
#include "light/LightManager.h"
#include "object/DrawableObject.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "core/Skybox.h"

class Scene {
public:
    Scene() : controller(camera) {}
    ~Scene() {}

    virtual void OnUpdate(float delta);
    virtual void OnDraw();
    virtual void OnKey(int key, int action) {}
    virtual void OnMouseButton(int button, int action, int mods, int x, int y) {}

    void AddShaderProgram(const std::string& name, const ref<ShaderProgram> shaderProgram);
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);
    void RemoveDrawableObject(const ref<DrawableObject>& drawableObject);
    void RemoveDrawableObject(int index);

    void SetAmbientLight(const glm::vec3& color);
    void AddLight(const ref<DirectionalLight>& light);
    void AddLight(const ref<PointLight>& light);
    void AddLight(const ref<SpotLight>& light);

    void SetAspectRatio(float aspect);

    void SetSkybox(const SkyboxFaces& faces);

    void DrawSkybox();

private:
    std::vector<ref<DrawableObject>> drawableObjects;
    Skybox skybox;

protected:
    Camera camera;
    Controller controller;
    ShaderProgramManager shaderProgramManager;
    LightManager lightManager;
};
