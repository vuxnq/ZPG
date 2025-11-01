#pragma once
#include <GL/glew.h>
#include <iostream>
#include "object/Model.h"

class ModelLoader {
public:
    ModelLoader(const char* name);
    Model Load();

private:
    std::vector<float> vertices;
};