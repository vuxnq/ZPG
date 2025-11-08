#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "object/Model.h"

class ModelLoader {
public:
    ModelLoader(const std::string& basedir);
    Model Load(const std::string& filename);

private:
    std::string basedir;

    GLuint LoadTexture(const std::string& filename);
};
