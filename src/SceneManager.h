#pragma once
#include <GL/glew.h>
#include <vector>
#include "Scene.h"

class SceneManager {
private:
    std::vector<Scene*> scenes;
    // active scenes atd atd
public:
    SceneManager();
    void AddScene();
    void SetActiveScene();
};