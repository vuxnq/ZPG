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


class Cv11Scene1 : public Scene {
public:
    Cv11Scene1() {
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

        AddDrawableObject(make_ref(new DrawableObject(
            make_ref(new Model(ml.Load("terrain.obj"))),
            make_ref(new ScaleTransform(0.5)),
            shaderProgramManager.GetShaderProgram("sp"))
        ));

        auto shrek = make_ref(new DrawableObject(
            shrekModel,
            make_ref(new Transformation()),
            shaderProgramManager.GetShaderProgram("sp")
        ));
        shrekIndex = shrek->GetIndex();
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
            }
            if (key == GLFW_KEY_C) {
                rotate = !rotate;
                printf("rotate: %d\n", rotate);
                UpdateTransformation();
            }
            if (key == GLFW_KEY_V) {
                loop = !loop;
                printf("loop: %d\n", loop);
                UpdateTransformation();
            }
        }
    }

    void OnMouseButton(int button, int action, int mods, int x, int y) override {
        if (action != GLFW_PRESS) return;
    	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

        GLbyte color[4]; GLfloat depth; GLuint index;
        Application::Get()->ReadPixel(x, y, color, depth, index);

    	printf("> [%d, %d]: %02hhx%02hhx%02hhx%02hhx, d: %f, index: %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
        glm::vec3 worldPos = utils::ScreenToWorld(x, y, depth, camera);

        points.push_back(worldPos);
        if (points.size() >= 4) {
            curves.push_back({points[0], points[1], points[2], points[3]});
            points.clear();
            duration += 2;
            UpdateTransformation();
        }
    }

    void UpdateTransformation() {
        RemoveDrawableObject(shrekIndex);

        auto shrek = make_ref(new DrawableObject(
            shrekModel,
            make_ref(new BezierTransform(curves, duration, rotate, loop)),
            shaderProgramManager.GetShaderProgram("sp")
        ));
        shrekIndex = shrek->GetIndex();

        AddDrawableObject(shrek);
    }

private:
    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {1, 1, 0, 0.1}));
    ModelLoader ml = ModelLoader("../assets/models/");
    ModelLoader ml3rdparty = ModelLoader("../assets/3rdparty/models/");

    ref<Model> shrekModel = make_ref(new Model(ml3rdparty.Load("shrek.obj")));

    int shrekIndex = 0;

    std::vector<glm::vec3> points = {};

    std::vector<CubicCurve> curves = {};
    float duration = 0;
    bool rotate = true;
    bool loop = true;
};


class Cv11Scene2 : public Scene {
public:
    Cv11Scene2() {
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

        AddDrawableObject(make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("track.obj"))),
            make_ref(new ScaleTransform(1)),
            shaderProgramManager.GetShaderProgram("sp"))
        ));

        auto carTransformation = make_ref(new Transformation());
        carTransformation->Add(make_ref(new ScaleTransform(0.0025)));
        carTransformation->Add(make_ref(new TranslateTransform(glm::vec3(0, 1.1, 0))));

        auto car = make_ref(new DrawableObject(
            carModel,
            carTransformation,
            shaderProgramManager.GetShaderProgram("sp")
        ));
        carIndex = car->GetIndex();
        AddDrawableObject(car);

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
            }
            if (key == GLFW_KEY_C) {
                rotate = !rotate;
                printf("rotate: %d\n", rotate);
                UpdateTransformation();
            }
            if (key == GLFW_KEY_V) {
                loop = !loop;
                printf("loop: %d\n", loop);
                UpdateTransformation();
            }
        }
    }

    void OnMouseButton(int button, int action, int mods, int x, int y) override {
        if (action != GLFW_PRESS) return;
    	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

        GLbyte color[4]; GLfloat depth; GLuint index;
        Application::Get()->ReadPixel(x, y, color, depth, index);

    	printf("> [%d, %d]: %02hhx%02hhx%02hhx%02hhx, d: %f, index: %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
        glm::vec3 worldPos = utils::ScreenToWorld(x, y, depth, camera);

        points.push_back(worldPos);
        if (points.size() >= 4) {
            curves.push_back({points[0], points[1], points[2], points[3]});
            auto last = points.back();
            points.clear();
            points.push_back(last);
            duration += 2;
            UpdateTransformation();
        }
    }

    void UpdateTransformation() {
        RemoveDrawableObject(carIndex);

        auto transformation = make_ref(new Transformation());
        transformation->Add(make_ref(new ScaleTransform(0.0025)));
        transformation->Add(make_ref(new TranslateTransform(glm::vec3(0, 0.5, 0))));
        transformation->Add(make_ref(new BezierTransform(curves, duration, rotate, loop)));

        auto car = make_ref(new DrawableObject(
            carModel,
            transformation,
            shaderProgramManager.GetShaderProgram("sp")
        ));
        carIndex = car->GetIndex();

        AddDrawableObject(car);
    }

private:
    ref<Flashlight> flashlight = make_ref(new Flashlight(glm::vec3(1.0, 1.0, 1.0), {1, 1, 0, 0.1}));
    ModelLoader ml3rdparty = ModelLoader("../assets/3rdparty/models/");

    ref<Model> carModel = make_ref(new Model(ml3rdparty.Load("banana-car.obj")));

    int carIndex = 0;

    std::vector<glm::vec3> points = {};

    std::vector<CubicCurve> curves = {};
    float duration = 0;
    bool rotate = true;
    bool loop = true;
};
