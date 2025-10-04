#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "core/Core.h"
#include "core/Scene.h"

class SceneManager {
public:
    SceneManager() {}
    ~SceneManager() {}

    void AddScene(const std::string& name, const ref<Scene>& scene);
    void SetActiveScene(const std::string& name);
    const ref<Scene>& GetActiveScene();

private:
    std::map<std::string, ref<Scene>> scenes;
    std::string activeScene = "";
};
