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
#include "core/Application.h"


class Cv9Scene1 : public Scene {
public:
    Cv9Scene1() {
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

        auto shrek = make_ref(new DrawableObject(
            make_ref(new Model(ml3rdparty.Load("shrek.obj"))),
            make_ref(new ScaleTransform(0.5)),
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
            glm::vec3 worldPos = ScreenToWorld(x, y, depth);
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
