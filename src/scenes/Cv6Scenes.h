#pragma once
#include "core/Scene.h"
#include "object/PointLight.h"

#include "assets/models/sphere.h"

class Cv6Scene1 : public Scene {
public:
    Cv6Scene1() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<ShaderProgram> shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));
        shaderProgramManager.AddShaderProgram("sp", shaderProgram);

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp"));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        for (int i = 0; i < 10; i++) {
            auto trans1 = make_ref(new Transformation());
            trans1->Add(make_ref(new ScaleTransform(0.2)));
            trans1->Add(make_ref(new TranslateTransform(glm::vec3(0.0 + (float)i, 0.0, 0.0))));
            auto sphere1 = make_ref(new DrawableObject(sphereModel, trans1, shaderProgramManager.GetShaderProgram("sp")));
            AddDrawableObject(sphere1);
        }

        auto light = make_ref(new PointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.5, 0.0)));
        AddPointLight(light);
        SetPointLights();
    }
};