#pragma once
#include <GL/glew.h>
#include <vector>
#include "Model.h"

class Scene {
public:
    Scene();
    ~Scene() {}

private:
    std::vector<Model*> models;
};