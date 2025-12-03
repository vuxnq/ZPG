#pragma once
#include <random>
#include <algorithm>
#include <vector>
#include <utility>
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
#include "core/Application.h"
#include "core/Utils.h"


class Cv10Scene1 : public Scene {
public:
    Cv10Scene1() {
        SetSkybox({
            "../assets/3rdparty/textures/skybox/pure/right.jpg",
            "../assets/3rdparty/textures/skybox/pure/left.jpg",
            "../assets/3rdparty/textures/skybox/pure/top.jpg",
            "../assets/3rdparty/textures/skybox/pure/bottom.jpg",
            "../assets/3rdparty/textures/skybox/pure/front.jpg",
            "../assets/3rdparty/textures/skybox/pure/back.jpg",
        });

        auto vertexShader = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));

        auto terrain = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("terrain.obj"))),
            make_ref(new ScaleTransform(0.5)),
            shaderProgramManager.GetShaderProgram("sp"))
        );
        AddDrawableObject(terrain);

        auto shrekTransformation = make_ref(new ScaleTransform(0.5));
        shrekTransformation->SetMatrix(glm::mat4(
            .5, 0 , 0 , 0,
            0 , .5, 0 , 0,
            0 , 0 , .5, 0,
            0 , 0 , 0 , 20
        ));

        auto shrek = make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("shrek.obj"))),
            shrekTransformation,
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(shrek);

        SetAmbientLight(glm::vec3(0.5, 0.5, 0.5));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.9, 0.8, 1.0), glm::vec3(0.0, -1.0 , 0.0), 1)));

        camera.AddSubscriber(flashlight.get());
        AddLight(flashlight);
    }

    void OnKey(int key, int action) override {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_F) {
                if (flashlight->GetAttenuation().intensity != 0.0) {
                    flashlight->SetAttenuation({ .intensity = 0.0 });
                    return;
                };
                flashlight->SetAttenuation(flashlight->GetFlashlightAttenuation());
            } else if (key == GLFW_KEY_E) {
                destroyMode = !destroyMode;
                printf("destroy mode: %d\n", destroyMode);
            }
        }
    }

    void OnMouseButton(int button, int action, int mods, int x, int y) override {
        if (action != GLFW_PRESS) return;
    	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        Application::Get()->ReadPixel(x, y, color, depth, index);

    	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

        if (destroyMode) {
            RemoveDrawableObject(index);
        } else {
            glm::vec3 worldPos = utils::ScreenToWorld(x, y, depth, camera);
            printf("unProject [%f,%f,%f]\n", worldPos.x, worldPos.y, worldPos.z);

            AddDrawableObject(make_ref(new DrawableObject(
                treeModel,
                make_ref(new TranslateTransform(worldPos)),
                shaderProgramManager.GetShaderProgram("sp")
            )));
        }
    }

private:
    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {1, 1, 0, 0.1}));
    ModelLoader ml = ModelLoader("../assets/models/");
    ModelLoader ml3rdparty = ModelLoader("../assets/3rdparty/models/");
    bool destroyMode = false;

    ref<Model> treeModel = make_ref(new Model(ml3rdparty.Load("tree.obj")));
};


class Cv10Scene2 : public Scene {
public:
    Cv10Scene2() {
        SetSkybox({
            "../assets/3rdparty/textures/skybox/pure/right.jpg",
            "../assets/3rdparty/textures/skybox/pure/left.jpg",
            "../assets/3rdparty/textures/skybox/pure/top.jpg",
            "../assets/3rdparty/textures/skybox/pure/bottom.jpg",
            "../assets/3rdparty/textures/skybox/pure/front.jpg",
            "../assets/3rdparty/textures/skybox/pure/back.jpg",
        });

        auto vertexShader = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddLight(make_ref(new DirectionalLight(glm::vec3(0.9, 0.8, 1.0), glm::vec3(0.0, -1.0 , 0.0), 1)));
        SetAmbientLight(glm::vec3(0.5, 0.5, 0.5));

        auto ground = make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("ground.obj"))),
            make_ref(new ScaleTransform(10.0f)),
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(ground);
        groundIndex = ground->GetIndex();
    }

    void OnUpdate(float delta) override {
        Scene::OnUpdate(delta);
        static float delayTimer = 0.0f;
        delayTimer += delta;

        if (moles.size() < maxMoles && delayTimer >= 2.0f) {
            int moleIndex = SpawnMole();
            moles.push_back(std::pair(moleIndex, 0.0f));
            delayTimer = 0.0f;
        }

        for (int i = 0; i < moles.size(); i++) {
            moles[i].second += delta;
            if (moles[i].second >= moleLifespan) {
                RemoveDrawableObject(moles[i].first);
                moles.erase(moles.begin() + i);
            }
        }
    }

    void OnMouseButton(int button, int action, int mods, int x, int y) override {
        if (action != GLFW_PRESS) return;
    	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        Application::Get()->ReadPixel(x, y, color, depth, index);

        if (index != groundIndex && index != 0) {
            RemoveDrawableObject(index);
            printf("score: %d\n", ++score);

            for (int i = 0; i < moles.size(); i++) {
                if (moles[i].first == (int)index) {
                    moles.erase(moles.begin() + i);
                    break;
                }
            }
        }
    }

    int SpawnMole() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> offset(-10.0f, 10.0f);

        float x = offset(gen);
        float z = offset(gen);

        float endX = offset(gen);
        float endZ = offset(gen);

        auto transform = make_ref(new PolylineTransform(
            {
                glm::vec3(x, -2, z),
                glm::vec3(x, 0, z),
                glm::vec3(offset(gen), 0, offset(gen)),
                glm::vec3(offset(gen), 0, offset(gen)),
                glm::vec3(offset(gen), 0, offset(gen)),
                glm::vec3(offset(gen), 0, offset(gen)),
                glm::vec3(endX, 0, endZ),
                glm::vec3(endX, -2, endZ)
            },
            moleLifespan
        ));

        auto mole = make_ref(new DrawableObject(
            moleModel,
            transform,
            shaderProgramManager.GetShaderProgram("sp")
        ));
        AddDrawableObject(mole);

        return mole->GetIndex();
    }

private:
    ModelLoader ml = ModelLoader("../assets/models/");
    ModelLoader ml3rdparty = ModelLoader("../assets/3rdparty/models/");
    ref<Model> moleModel = make_ref(new Model(ml3rdparty.Load("shrek.obj")));
    int groundIndex;

    std::vector<std::pair<int, float>> moles;
    float moleLifespan = 5.0;
    int maxMoles = 3;

    int score = 0;
};


class Cv10Scene3 : public Scene {
public:
    Cv10Scene3() {
        SetSkybox({
            "../assets/textures/skybox/space/right.png",
            "../assets/textures/skybox/space/left.png",
            "../assets/textures/skybox/space/top.png",
            "../assets/textures/skybox/space/bottom.png",
            "../assets/textures/skybox/space/front.png",
            "../assets/textures/skybox/space/back.png",
        });

        auto vertexShader = make_ref(new Shader("../assets/shaders/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/shaders/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderConstant = make_ref(new Shader("../assets/shaders/fs_constant.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_sun", make_ref(new ShaderProgram({vertexShader, fragmentShaderConstant})));

        // sun ----------------------------------------------------------------
        auto sunTransformation = make_ref(new Transformation());
        sunTransformation->Add(make_ref(new DynamicRotateTransform(180, glm::vec3(0, 1, 0), speed)));

        auto sunLight = make_ref(new PointLight(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), {1, 0, 0, 0}));
        AddLight(sunLight);
        AddDrawableObject(make_ref(new LightObject(
            make_ref(new Model(ml.Load("sun.obj"))),
            sunTransformation,
            shaderProgramManager.GetShaderProgram("sp_sun"),
            sunLight
        )));

        // earth --------------------------------------------------------------
        auto earthBaseTransformation = make_ref(new Transformation());
        earthBaseTransformation->Add(make_ref(new RotateTransform(23.5, glm::vec3(0, 0, 1))));
        earthBaseTransformation->Add(make_ref(new TranslateTransform(glm::vec3(3, 0, 0))));
        earthBaseTransformation->Add(make_ref(new DynamicRotateTransform(360, glm::vec3(0, 1, 0), speed)));

        auto earthTransformation = make_ref(new Transformation());
        earthTransformation->Add(make_ref(new ScaleTransform(0.3)));
        earthTransformation->Add(make_ref(new DynamicRotateTransform(360 * 365, glm::vec3(0, 1, 0), speed)));
        earthTransformation->Add(make_ref(new Transformation(*earthBaseTransformation.get())));

        AddDrawableObject(make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("earth.obj"))),
            earthTransformation,
            shaderProgramManager.GetShaderProgram("sp")
        )));

        // moon ---------------------------------------------------------------
        auto moonTransformation = make_ref(new Transformation());
        moonTransformation->Add(make_ref(new ScaleTransform(0.3 / 4)));
        moonTransformation->Add(make_ref(new RotateTransform(180, glm::vec3(0, 1, 0))));
        moonTransformation->Add(make_ref(new TranslateTransform(glm::vec3(1, 0, 0))));
        moonTransformation->Add(make_ref(new DynamicRotateTransform(360 * 12, glm::vec3(0, 1, 0), speed)));

        moonTransformation->Add(make_ref(new Transformation(*earthBaseTransformation.get())));

        AddDrawableObject(make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("moon.obj"))),
            moonTransformation,
            shaderProgramManager.GetShaderProgram("sp")
        )));

        // login --------------------------------------------------------------
        auto loginTransformation = make_ref(new Transformation());
        loginTransformation->Add(make_ref(new ScaleTransform(0.3 / 4)));
        loginTransformation->Add(make_ref(new RotateTransform(180, glm::vec3(0, 1, 0))));
        loginTransformation->Add(make_ref(new TranslateTransform(glm::vec3(-1, 0, 0))));
        loginTransformation->Add(make_ref(new DynamicRotateTransform(-360 * 12, glm::vec3(0, 1, 0), speed)));

        loginTransformation->Add(make_ref(new Transformation(*earthBaseTransformation.get())));

        AddDrawableObject(make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("login.obj"))),
            loginTransformation,
            shaderProgramManager.GetShaderProgram("sp")
        )));


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
    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {1, 1, 0, 0.1}));
    ModelLoader ml = ModelLoader("../assets/models/");
    float speed = 0.005;
};
