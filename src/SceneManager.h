#pragma once
#include <GL/glew.h>
#include <vector>
#include "Core.h"
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager() {}

    void AddScene();
    void SetActiveScene();

private:
    std::vector<ref<Scene>> scenes;
};