#pragma once
#include <GL/glew.h>
#include <vector>
#include "Model.h"

class Scene {
private:
    std::vector<Model*> models;
public:
    Scene();
};