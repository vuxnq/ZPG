#pragma once
#include <random>
#include <algorithm>
#include "core/Scene.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "light/LightObject.h"
#include "light/Flashlight.h"

#include "assets/vertices/sphere.h"
#include "assets/vertices/plain.h"
#include "assets/vertices/tree.h"
#include "assets/vertices/bushes.h"

#include "object/ModelLoader.h"


class Cv8Scene1 : public Scene {
public:
    Cv8Scene1() {
        SetSkybox({
            "../assets/textures/skybox/trees/posx.jpg",
            "../assets/textures/skybox/trees/negx.jpg",
            "../assets/textures/skybox/trees/posy.jpg",
            "../assets/textures/skybox/trees/negy.jpg",
            "../assets/textures/skybox/trees/posz.jpg",
            "../assets/textures/skybox/trees/negz.jpg",
        });

        auto vertexShader = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto vertexShaderOld = make_ref(new Shader("../assets/shaders/vs_old.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderFirefly = make_ref(new Shader("../assets/shaders/fs_constant_firefly.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_old", make_ref(new ShaderProgram({vertexShaderOld, fragmentShader})));
        AddShaderProgram("sp_old_firefly", make_ref(new ShaderProgram({vertexShaderOld, fragmentShaderFirefly})));

        auto bushesVBO = make_ref(new VertexBuffer(bushes, sizeof(bushes), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto bushesVAO = make_ref(new VertexArray(bushesVBO));
        auto bushesModel = make_ref(new Model(bushesVAO));

        auto treeVBO = make_ref(new VertexBuffer(tree, sizeof(tree), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto treeVAO = make_ref(new VertexArray(treeVBO));
        auto treeModel = make_ref(new Model(treeVAO));

        auto plainVBO = make_ref(new VertexBuffer(plain, sizeof(plain), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto plainVAO = make_ref(new VertexArray(plainVBO));
        auto plainModel = make_ref(new Model(plainVAO));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> rTreeOffset(-plainSize, plainSize);
        std::uniform_real_distribution<float> rBushOffset(-0.5f, 0.5f);
        std::uniform_real_distribution<float> rAngle(0.0f, 360.0f);
        std::uniform_real_distribution<float> rScale(0.6f, 1.0f);

        // trees
        for (int i = 0; i < treeCount; i++) {
            auto treeTransform = make_ref(new Transformation());
            treeTransform->Add(make_ref(new ScaleTransform(rScale(gen))));
            treeTransform->Add(make_ref(new RotateTransform(rAngle(gen), glm::vec3(0.0f, 1.0f, 0.0f))));
            treeTransform->Add(make_ref(new TranslateTransform(glm::vec3(rTreeOffset(gen), 0.0f, rTreeOffset(gen)))));
            auto treeObject = make_ref(new DrawableObject(treeModel, treeTransform, shaderProgramManager.GetShaderProgram("sp_old")));

            // bushes around the tree
            for (int j = 0; j < 10; j++) {
                if (rand() % 2) continue;

                auto bushesTransform = make_ref(new Transformation());
                bushesTransform->Add(make_ref(new ScaleTransform(rScale(gen))));
                bushesTransform->Add(make_ref(new RotateTransform(rAngle(gen), glm::vec3(0.0f, 1.0f, 0.0f))));
                bushesTransform->Add(make_ref(new TranslateTransform(glm::vec3(rBushOffset(gen), 0.0f, rBushOffset(gen)))));
                bushesTransform->Add(treeTransform);
                auto bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgramManager.GetShaderProgram("sp_old")));
                AddDrawableObject(bushesObject);
            }
            AddDrawableObject(treeObject);
        }

        // bushes
        for (int i = 0; i < (int)(pow(plainSize, 2) * bushesDensity); i++) {
            auto bushesTransform = make_ref(new Transformation());
            bushesTransform->Add(make_ref(new ScaleTransform(rScale(gen))));
            bushesTransform->Add(make_ref(new RotateTransform(rAngle(gen), glm::vec3(0.0f, 1.0f, 0.0f))));
            bushesTransform->Add(make_ref(new TranslateTransform(glm::vec3(rTreeOffset(gen), 0.0f, rTreeOffset(gen)))));
            auto bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgramManager.GetShaderProgram("sp_old")));
            AddDrawableObject(bushesObject);
        }

        // fireflies
        for (int i = 0; i < fireflyCount; i++) {
            auto fireflyTransform = make_ref(new Transformation());
            fireflyTransform->Add(make_ref(new ScaleTransform(0.03)));
            fireflyTransform->Add(make_ref(new TranslateTransform(glm::vec3(rBushOffset(gen), rBushOffset(gen), rBushOffset(gen)))));
            fireflyTransform->Add(make_ref(new DynamicRotateTransform(90, glm::vec3(rBushOffset(gen), (float)rBushOffset(gen), rBushOffset(gen)), 1)));
            fireflyTransform->Add(make_ref(new TranslateTransform(glm::vec3(rTreeOffset(gen), std::max(rTreeOffset(gen) / 2, 0.5f), rTreeOffset(gen)))));
            auto fireflyLight = make_ref(new PointLight(glm::vec3(0.8, 1.0, 0.8), glm::vec3(0), {0.05, 0.05, 1.0, 1.0}));
            auto fireflyObject = make_ref(new LightObject(sphereModel, fireflyTransform, shaderProgramManager.GetShaderProgram("sp_old_firefly"), fireflyLight));
            AddLight(fireflyLight);
            AddDrawableObject(fireflyObject);
        }

        auto plainObject = make_ref(new DrawableObject(plainModel, make_ref(new ScaleTransform(plainSize)), shaderProgramManager.GetShaderProgram("sp_old")));
        AddDrawableObject(plainObject);

        SetAmbientLight(glm::vec3(0.025, 0.025, 0.025));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.0, 0.3, 0.9), glm::vec3(-1.0, -1.0 , -1.0), 0.1)));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.1, 0.1, 0.8), glm::vec3(1.0, -1.0 , 1.0), 0.1)));
        // AddLight(make_ref(new SpotLight(glm::vec3(1.0, 0.0 , 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, -1.0 , 0.0), { .intensity = 10.0 })));
        // AddLight(make_ref(new SpotLight(glm::vec3(1.0, 1.0 , 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0 , -1.0), {})));

        camera.AddSubscriber(flashlight.get());
        AddLight(flashlight);
    }

    void OnKey(int key, int action) override {
        if (action == GLFW_PRESS && key == GLFW_KEY_F) {
            if (flashlight->GetAttenuation().intensity != 0.0) {
                flashlight->SetAttenuation({ .intensity = 0.0 });
                return;
            };
            flashlight->SetAttenuation(flashlight->GetFlashlightAttenuation());
        }
    }

private:
    float plainSize = 10.0f;
    int bushesDensity = 4;
    int treeCount = 50;
    int fireflyCount = 50;

    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {}));
};


class Cv8Scene2 : public Scene {
public:
    Cv8Scene2() {
        SetSkybox({
            "../assets/3rdparty/textures/skybox/pure/right.jpg",
            "../assets/3rdparty/textures/skybox/pure/left.jpg",
            "../assets/3rdparty/textures/skybox/pure/top.jpg",
            "../assets/3rdparty/textures/skybox/pure/bottom.jpg",
            "../assets/3rdparty/textures/skybox/pure/front.jpg",
            "../assets/3rdparty/textures/skybox/pure/back.jpg",
        });

        auto shaderVertex = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto shaderFragment = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));
        AddShaderProgram("sp", make_ref(new ShaderProgram({shaderVertex, shaderFragment})));

        SetAmbientLight(glm::vec3(0.05, 0.05, 0.05));
        AddLight(make_ref(new SpotLight(glm::vec3(1, 0, 0), glm::vec3(0, 3, 0), glm::vec3(0, -1, 0), {})));

        auto ml = ModelLoader("../assets/3rdparty/models/");

        auto obj = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("shrek.obj"))),
            make_ref(new ScaleTransform(1)),
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(obj);

        camera.AddSubscriber(flashlight.get());
        AddLight(flashlight);

    }

    void OnKey(int key, int action) override {
        if (action == GLFW_PRESS && key == GLFW_KEY_F) {
            if (flashlight->GetAttenuation().intensity != 0.0) {
                flashlight->SetAttenuation({ .intensity = 0.0 });
                return;
            };
            flashlight->SetAttenuation(flashlight->GetFlashlightAttenuation());
        }
    }

private:
    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {}));
};
