#pragma once
#include <GL/glew.h>
#include <vector>
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager() {}

    void AddScene();
    void SetActiveScene();

private:
    std::vector<Scene*> scenes;
};