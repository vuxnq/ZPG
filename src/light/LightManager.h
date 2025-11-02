#pragma once
#include <GL/glew.h>
#include <vector>
#include "core/Core.h"
#include "core/Observer.h"
#include "light/DirectionalLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

class LightManager : public Publisher, public Subscriber {
public:
    LightManager() {}
    ~LightManager() {}

    void SetAmbientLight(const glm::vec3& color);

    void AddLight(const ref<DirectionalLight>& light);
    void AddLight(const ref<PointLight>& light);
    void AddLight(const ref<SpotLight>& light);

    void OnNotify(const Event& event) override;

private:
    std::vector<ref<DirectionalLight>> directionalLights;
    std::vector<ref<PointLight>> pointLights;
    std::vector<ref<SpotLight>> spotLights;
};