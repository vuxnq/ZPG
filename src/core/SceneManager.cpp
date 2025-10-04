#include "core/SceneManager.h"

void SceneManager::AddScene(const std::string& name, const ref<Scene>& scene) {
    scenes[name] = scene;
    if (activeScene == "") {
        SetActiveScene(name);
    }
}

void SceneManager::SetActiveScene(const std::string& name) {
    if (!scenes.contains(name)) {
        fprintf(stderr, "Scene '%s' does not exist in Scene Manager.\n", name);
        exit(EXIT_FAILURE);
    }
    activeScene = name;
}

const ref<Scene>& SceneManager::GetActiveScene() {
    if (!scenes.contains(activeScene)) {
        fprintf(stderr, "No scene has been added to Scene Manager.\n");
        exit(EXIT_FAILURE);
    }
    return scenes[activeScene];
}
