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
            "../assets/3rdparty/textures/skybox/wwwtyro/right.png",
            "../assets/3rdparty/textures/skybox/wwwtyro/left.png",
            "../assets/3rdparty/textures/skybox/wwwtyro/top.png",
            "../assets/3rdparty/textures/skybox/wwwtyro/bottom.png",
            "../assets/3rdparty/textures/skybox/wwwtyro/front.png",
            "../assets/3rdparty/textures/skybox/wwwtyro/back.png",
        });

        auto vertexShader = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto vertexShaderOld = make_ref(new Shader("../assets/shaders/vs_old.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderFirefly = make_ref(new Shader("../assets/shaders/fs_constant_firefly.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_old", make_ref(new ShaderProgram({vertexShaderOld, fragmentShader})));
        AddShaderProgram("sp_old_firefly", make_ref(new ShaderProgram({vertexShaderOld, fragmentShaderFirefly})));

        auto ml = ModelLoader("../assets/models/");
        auto ml3rdparty = ModelLoader("../assets/3rdparty/models/");

        // auto bushesVBO = make_ref(new VertexBuffer(bushes, sizeof(bushes), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        // auto bushesVAO = make_ref(new VertexArray(bushesVBO));
        // auto bushesModel = make_ref(new Model(bushesVAO));
        auto bushesModel = make_ref(new Model(ml.Load("grass.obj")));

        auto treeVBO = make_ref(new VertexBuffer(tree, sizeof(tree), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto treeVAO = make_ref(new VertexArray(treeVBO));
        auto treeModel = make_ref(new Model(treeVAO));
        // auto treeModel = make_ref(new Model(ml3rdparty.Load("tree.obj")));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> rTreeOffset(-plainSize, plainSize);
        std::uniform_real_distribution<float> rBushOffset(-0.5f, 0.5f);
        std::uniform_real_distribution<float> rAngle(0.0f, 360.0f);
        std::uniform_real_distribution<float> rScale(0.6f, 1.0f);
        std::uniform_real_distribution<float> rTreeScale(0.6f, 1.0f);
        // std::uniform_real_distribution<float> rTreeScale(1.3f, 2.0f);


        // trees
        for (int i = 0; i < treeCount; i++) {
            auto treeTransform = make_ref(new Transformation());
            treeTransform->Add(make_ref(new ScaleTransform(rTreeScale(gen))));
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
                auto bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgramManager.GetShaderProgram("sp")));
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
            auto bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgramManager.GetShaderProgram("sp")));
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

        auto plainObject = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("ground.obj"))),
            make_ref(new ScaleTransform(plainSize)),
            shaderProgramManager.GetShaderProgram("sp"))
        );
        AddDrawableObject(plainObject);


        auto shrek = make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("shrek.obj"))),
            make_ref(new ScaleTransform(0.5)),
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(shrek);

        auto fionaT = make_ref(new Transformation());
        fionaT->Add(make_ref(new ScaleTransform(0.5)));
        fionaT->Add(make_ref(new TranslateTransform(glm::vec3(0, 0, -1))));
        fionaT->Add(make_ref(new RotateTransform(180, glm::vec3(0, 1, 0))));
        auto fiona = make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("fiona.obj"))),
            fionaT,
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(fiona);

        auto toilet = make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("toiled.obj"))),
            make_ref(new ScaleTransform(0.5)),
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(toilet);

        SetAmbientLight(glm::vec3(0.025, 0.025, 0.025));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.0, 0.3, 0.9), glm::vec3(-1.0, -1.0 , -1.0), 0.1)));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.1, 0.1, 0.8), glm::vec3(1.0, -1.0 , 1.0), 0.1)));

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
    int treeCount = 20;
    int fireflyCount = 20;

    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {1, 1, 0, 0.1}));
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

        SetAmbientLight(glm::vec3(0.5, 0.5, 0.5));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.9, 0.9, 1), glm::vec3(0, -1, 0), 1)));
        AddLight(make_ref(new PointLight(glm::vec3(1, 0, 1), glm::vec3(0, 2, 1), {})));

        auto ml = ModelLoader("../assets/3rdparty/models/");

        auto obj = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("shrek.obj"))),
            make_ref(new ScaleTransform(1)),
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(obj);

        auto obj2 = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("fiona.obj"))),
            make_ref(new TranslateTransform(glm::vec3(1.5, 0, 0))),
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(obj2);

        auto obj3 = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("toiled.obj"))),
            make_ref(new TranslateTransform(glm::vec3(0, 0, 2))),
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(obj3);

        auto obj4t = make_ref(new Transformation());
        obj4t->Add(make_ref(new ScaleTransform(1)));
        obj4t->Add(make_ref(new TranslateTransform(glm::vec3(5, 0, 2))));
        auto obj4 = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("tree.obj"))),
            obj4t,
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(obj4);


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
