#pragma once
#include <GL/glew.h>
#include <vector>
#include "Core.h"
#include "Model.h"

class Scene {
public:
    Scene();
    ~Scene() {}

private:
    std::vector<ref<Model>> models;
};