#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Camera.h"
#include "core/Controller.h"
#include "object/DrawableObject.h"

class Scene {
public:
    Scene() : controller(camera) {}
    ~Scene() {}

    virtual void OnUpdate(float delta); // TODO: add renderer class mb drawableobj by se nemel sam kreslit
    void AddDrawableObject(const ref<DrawableObject>& drawableObject);

private:
    std::vector<ref<DrawableObject>> drawableObjects;

protected:
    Camera camera;
    Controller controller;
};