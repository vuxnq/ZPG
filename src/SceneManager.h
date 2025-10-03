#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Core.h"
#include "Scene.h"

class SceneManager {
public:
    SceneManager() {}
    ~SceneManager() {}

    void AddScene(const std::string& name, const ref<Scene>& scene) {
        scenes[name] = scene;
        if (activeScene == "") {
            SetActiveScene(name);
        }
    }
    void SetActiveScene(const std::string& name) {
        if (!scenes.contains(name)) {
            fprintf(stderr, "Scene '%s' does not exist in Scene Manager.\n", name);
            exit(EXIT_FAILURE);
        }
        activeScene = name;
    }
    const ref<Scene>& GetActiveScene() {
        if (!scenes.contains(activeScene)) {
            fprintf(stderr, "No scene has been added to Scene Manager.\n");
            exit(EXIT_FAILURE);
        }
        return scenes[activeScene];
    }

private:
    std::map<std::string, ref<Scene>> scenes;
    std::string activeScene = "";
};