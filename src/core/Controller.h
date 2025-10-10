#pragma once
#include <GL/glew.h>
#include "core/Core.h"
#include "core/Camera.h"

class Controller {
public:
    Controller(ref<Camera> camera) {
        this->camera = camera;
    }

    ~Controller() {}

private:
    ref<Camera> camera;
};