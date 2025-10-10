#pragma once
#include "core/Scene.h"
#include <random>

#include "assets/models/bushes.h"
#include "assets/models/gift.h"
#include "assets/models/plain.h"
#include "assets/models/sphere.h"
#include "assets/models/suzi_flat.h"
#include "assets/models/suzi_smooth.h"
#include "assets/models/tree.h"

// scene1 - triangle
class Cv3Scene1 : public Scene {
public:
    Cv3Scene1() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

        camera.AddSubscriber(shaderProgram);

        float points_triangle[] = {
            // pos              // color
            0.0f, 0.5f, -1.0f,   1.f, 0.f, 0.f, 1.f,
            0.5f, -0.5f, -1.0f,  0.f, 1.f, 0.f, 1.f,
            -0.5f, -0.5f, -1.0f, 0.f, 0.f, 1.f, 1.f,
        };

        ref<VertexBuffer> triangleVBO = make_ref(new VertexBuffer(points_triangle, sizeof(points_triangle)));
        triangleVBO->SetLayout({
            {ElementType::Float, 3},
            {ElementType::Float, 4}
        });
        ref<VertexArray> triangleVAO = make_ref(new VertexArray(triangleVBO));
        ref<Model> triangleModel = make_ref(new Model(triangleVAO));
        ref<DrawableObject> triangleObject = make_ref(new DrawableObject(
            triangleModel,
            make_ref(new DynamicRotateTransform(90, glm::vec3(0.0f, 0.0f, 1.0f), 1)),
            shaderProgram
        ));

        AddDrawableObject(triangleObject);
    }

private:
    ref<ShaderProgram> shaderProgram;
};



// scene2 - balls :p
class Cv3Scene2 : public Scene {
public:
    Cv3Scene2() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader_normal.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

        camera.AddSubscriber(shaderProgram);

        ref<VertexBuffer> sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> sphereVAO = make_ref(new VertexArray(sphereVBO));
        ref<Model> sphereModel = make_ref(new Model(sphereVAO));
        auto so1T = make_ref(new Transformation());
        so1T->Add(make_ref(new ScaleTransform(0.2)));
        so1T->Add(make_ref(new TranslateTransform(glm::vec3(-0.5f, 0.5f, 0.0f))));
        auto so2T = make_ref(new Transformation());
        so2T->Add(make_ref(new ScaleTransform(0.2)));
        so2T->Add(make_ref(new TranslateTransform(glm::vec3(0.5f, 0.5f, 0.0f))));
        auto so3T = make_ref(new Transformation());
        so3T->Add(make_ref(new ScaleTransform(0.2)));
        so3T->Add(make_ref(new TranslateTransform(glm::vec3(-0.5f, -0.5f, 0.0f))));
        auto so4T = make_ref(new Transformation());
        so4T->Add(make_ref(new ScaleTransform(0.2)));
        so4T->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.0f, 0.0f))));
        ref<DrawableObject> sphereObject1 = make_ref(new DrawableObject(sphereModel, so1T, shaderProgram));
        ref<DrawableObject> sphereObject2 = make_ref(new DrawableObject(sphereModel, so2T, shaderProgram));
        ref<DrawableObject> sphereObject3 = make_ref(new DrawableObject(sphereModel, so3T, shaderProgram));
        ref<DrawableObject> sphereObject4 = make_ref(new DrawableObject(sphereModel, so4T, shaderProgram));

        AddDrawableObject(sphereObject1);
        AddDrawableObject(sphereObject2);
        AddDrawableObject(sphereObject3);
        AddDrawableObject(sphereObject4);
    }

private:
    ref<ShaderProgram> shaderProgram;
};



// scene3 - více různých objektů s různými shader programy a transformacemi
class Cv3Scene3 : public Scene {
public:
    Cv3Scene3() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader_normal.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderGrayscale = make_ref(new Shader("../assets/fragment_shader_grayscale.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderYellow = make_ref(new Shader("../assets/fragment_shader_yellow.glsl", GL_FRAGMENT_SHADER));
        std::vector<ref<ShaderProgram>> shaders = {
            make_ref(new ShaderProgram({vertexShader, fragmentShader})),
            make_ref(new ShaderProgram({vertexShader, fragmentShaderGrayscale})),
            make_ref(new ShaderProgram({vertexShader, fragmentShaderYellow}))
        };

        for (auto& shader : shaders) {
            camera.AddSubscriber(shader);
        }

        std::vector<std::tuple<ElementType::Type, int>> layout = {{ElementType::Float, 3}, {ElementType::Float, 3}};
        std::vector<ref<Model>> models = {
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(bushes, sizeof(bushes), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(gift, sizeof(gift), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(plain, sizeof(plain), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(sphere, sizeof(sphere), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(suziFlat, sizeof(suziFlat), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(suziSmooth, sizeof(suziSmooth), layout)))))),
            make_ref(new Model(make_ref(new VertexArray(make_ref(new VertexBuffer(tree, sizeof(tree), layout))))))
        };

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> offsetd(-5.0f, 5.0f);
        std::uniform_real_distribution<float> axisd(-1.0f, 1.0f);
        std::uniform_real_distribution<float> scaled(0.1f, 0.4f);
        std::uniform_real_distribution<float> spind(-30.0f, 30.0f);
        std::uniform_real_distribution<float> speedd(0.1f, 10.0f);

        for (int i = 0; i < 20; i++) {
            auto randomModel = models[i % models.size()];
            auto randomShader = shaders[i % shaders.size()];
            auto transform = make_ref(new Transformation());
            transform->Add(make_ref(new TranslateTransform(glm::vec3(offsetd(gen), offsetd(gen), axisd(gen)))));
            transform->Add(make_ref(new DynamicRotateTransform(spind(gen), glm::vec3(axisd(gen), axisd(gen), axisd(gen)), speedd(gen))));
            transform->Add(make_ref(new ScaleTransform(scaled(gen))));
            auto obj = make_ref(new DrawableObject(randomModel, transform, randomShader));
            AddDrawableObject(obj);
        }
    }
};



// scene4 - test
class Cv3Scene4 : public Scene {
public:
    Cv3Scene4() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader_normal.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));


        camera.AddSubscriber(shaderProgram);


        std::vector<std::tuple<ElementType::Type, int>> layout = {{ElementType::Float, 3}, {ElementType::Float, 3}};
        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), layout));
        auto sphereModel = make_ref(new Model(make_ref(new VertexArray(sphereVBO))));

        auto t = make_ref<Transformation>();
        t->Add(make_ref(new TranslateTransform(glm::vec3(1.0f, 1.0f, 0.0f))));
        t->Add(make_ref(new DynamicRotateTransform(45, glm::vec3(0.0f, 1.0f, 0.0f), 3)));
        t->Add(make_ref(new ScaleTransform(0.5)));
        t->Add(make_ref(new RotateTransform(45, glm::vec3(0.0f, 0.0f, 1.0f))));
        t->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.5f, 0.0f))));
        t->Add(make_ref(new DynamicTranslateTransform(glm::vec3(0.0f, -0.5f, 0.0f), 0.5)));
        t->Add(make_ref(new DynamicScaleTransform(-1, 0.1)));

        ref<DrawableObject> ballz = make_ref(new DrawableObject(sphereModel, t, shaderProgram));

        ref<Scene> messScene = make_ref(new Scene());
        AddDrawableObject(ballz);
    }

private:
    ref<ShaderProgram> shaderProgram;
};
