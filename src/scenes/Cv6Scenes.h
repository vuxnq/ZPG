#pragma once
#include <random>
#include <algorithm>
#include "core/Scene.h"
#include "light/PointLight.h"
#include "light/LightObject.h"

#include "assets/models/sphere.h"
#include "assets/models/plain.h"
#include "assets/models/tree.h"
#include "assets/models/bushes.h"

class Cv6Scene1 : public Scene {
public:
    Cv6Scene1() {
        auto vertexShader = make_ref(new Shader("../assets/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/fs.glsl", GL_FRAGMENT_SHADER));
        auto shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

        AddShaderProgram("sp", shaderProgram);

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        for (int i = 0; i < 10; i++) {
            auto trans1 = make_ref(new Transformation());
            trans1->Add(make_ref(new ScaleTransform(0.2)));
            trans1->Add(make_ref(new TranslateTransform(glm::vec3(0.0 + (float)i, 0.0, -2.0))));
            auto sphere1 = make_ref(new DrawableObject(sphereModel, trans1, shaderProgramManager.GetShaderProgram("sp")));
            AddDrawableObject(sphere1);
        }

        auto light = make_ref(new PointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), 30));
        AddPointLight(light);

        auto circling = make_ref(new Transformation());
        circling->Add(make_ref(new ScaleTransform(0.1)));
        circling->Add(make_ref(new TranslateTransform(glm::vec3(1.0, 0.0, 0.0))));
        circling->Add(make_ref(new DynamicRotateTransform(20, glm::vec3(0.0, 1.0, 0.0), 4)));

        auto redlight = make_ref(new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), 10));
        AddPointLight(redlight);
        auto lighObject = make_ref(new LightObject(sphereModel, circling, shaderProgramManager.GetShaderProgram("sp"), redlight));
        AddDrawableObject(lighObject);
    }
};


class Cv6Scene2 : public Scene {
public:
    Cv6Scene2() {
        auto vertexShader = make_ref(new Shader("../assets/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderFirefly = make_ref(new Shader("../assets/fs_constant_firefly.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_firefly", make_ref(new ShaderProgram({vertexShader, fragmentShaderFirefly})));

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
            auto treeObject = make_ref(new DrawableObject(treeModel, treeTransform, shaderProgramManager.GetShaderProgram("sp")));

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
            auto fireflyLight = make_ref(new PointLight(glm::vec3(0.8, 1.0, 0.8), glm::vec3(0), 1));
            auto fireflyObject = make_ref(new LightObject(sphereModel, fireflyTransform, shaderProgramManager.GetShaderProgram("sp_firefly"), fireflyLight));
            AddPointLight(fireflyLight);
            AddDrawableObject(fireflyObject);
        }

        auto plainObject = make_ref(new DrawableObject(plainModel, make_ref(new ScaleTransform(plainSize)), shaderProgramManager.GetShaderProgram("sp")));
        AddDrawableObject(plainObject);

        auto blueLight = make_ref(new PointLight(glm::vec3(0.0, 0.3, 0.9), glm::vec3(10.0f, 10.0f, 10.0f), 300));
        auto purpleLight = make_ref(new PointLight(glm::vec3(0.1, 0.1, 0.8), glm::vec3(-10.0f, 10.0f, -10.0f), 300));
        AddPointLight(blueLight);
        AddPointLight(purpleLight);
    }

private:
    float plainSize = 10.0f;
    int bushesDensity = 4;
    int treeCount = 50;
    int fireflyCount = 20;
};



class Cv6Scene3 : public Scene {
public:
    Cv6Scene3() {
        auto vertexShader = make_ref(new Shader("../assets/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderConstantSun = make_ref(new Shader("../assets/fs_constant_sun.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderLambert = make_ref(new Shader("../assets/fs_lambert.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_constant", make_ref(new ShaderProgram({vertexShader, fragmentShaderConstantSun})));
        AddShaderProgram("sp_lambert", make_ref(new ShaderProgram({vertexShader, fragmentShaderLambert})));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        auto sunTransform = make_ref(new Transformation());
        sunTransform->Add(make_ref(new ScaleTransform(0.8)));
        sunTransform->Add(make_ref(new DynamicRotateTransform(10, glm::vec3(0.0f, 1.0f, 0.0f), 1)));


        auto earthTransform = make_ref(new Transformation());
        earthTransform->Add(make_ref(new ScaleTransform(0.3)));
        earthTransform->Add(make_ref(new DynamicRotateTransform(45, glm::vec3(0.0f, 1.0f, 0.0f), 1)));
        earthTransform->Add(make_ref(new RotateTransform(25, glm::vec3(0.0f, 0.0f, 1.0f))));

        earthTransform->Add(make_ref(new TranslateTransform(glm::vec3(5.0f, 0.0f, 0.0f))));
        earthTransform->Add(make_ref(new DynamicRotateTransform(20, glm::vec3(0.0f, 1.0f, 0.0f), 1)));


        auto moonTransform = make_ref(new Transformation());
        moonTransform->Add(make_ref(new ScaleTransform(0.1)));
        moonTransform->Add(make_ref(new DynamicRotateTransform(45, glm::vec3(0.0f, 1.0f, 0.0f), 1)));

        moonTransform->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.0f, 1.0f))));
        moonTransform->Add(make_ref(new DynamicRotateTransform(20, glm::vec3(0.0f, 1.0f, 0.0f), 10)));
        moonTransform->Add(make_ref(new RotateTransform(25, glm::vec3(0.0f, 0.0f, 1.0f))));

        moonTransform->Add(make_ref(new TranslateTransform(glm::vec3(5.0f, 0.0f, 0.0f))));
        moonTransform->Add(make_ref(new DynamicRotateTransform(20, glm::vec3(0.0f, 1.0f, 0.0f), 1)));


        auto sunObject = make_ref(new DrawableObject(sphereModel, sunTransform, shaderProgramManager.GetShaderProgram("sp_constant")));
        auto earthObject = make_ref(new DrawableObject(sphereModel, earthTransform, shaderProgramManager.GetShaderProgram("sp")));
        auto moonObject = make_ref(new DrawableObject(sphereModel, moonTransform, shaderProgramManager.GetShaderProgram("sp_lambert")));

        AddDrawableObject(sunObject);
        AddDrawableObject(earthObject);
        AddDrawableObject(moonObject);

        auto sunPointLight = make_ref(new PointLight(glm::vec3(1.0, 1.0, 0.9), glm::vec3(0.0, 0.0, 0.0), 1000));
        AddPointLight(sunPointLight);
    }
};



class Cv6Scene4 : public Scene {
public:
    Cv6Scene4() {
        auto vertexShader = make_ref(new Shader("../assets/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShader = make_ref(new Shader("../assets/fs.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderWrong = make_ref(new Shader("../assets/fs_wrong.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        AddShaderProgram("sp_wrong", make_ref(new ShaderProgram({vertexShader, fragmentShaderWrong})));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        auto trans1 = make_ref(new Transformation());
        trans1->Add(make_ref(new ScaleTransform(0.2)));
        trans1->Add(make_ref(new TranslateTransform(glm::vec3(0.0, 0.5, -2.0))));
        auto sphere1 = make_ref(new DrawableObject(sphereModel, trans1, shaderProgramManager.GetShaderProgram("sp")));
        AddDrawableObject(sphere1);

        auto trans2 = make_ref(new Transformation());
        trans2->Add(make_ref(new ScaleTransform(0.2)));
        trans2->Add(make_ref(new TranslateTransform(glm::vec3(0.5, 0.0, -2.0))));
        auto sphere2 = make_ref(new DrawableObject(sphereModel, trans2, shaderProgramManager.GetShaderProgram("sp")));
        AddDrawableObject(sphere2);

        auto trans3 = make_ref(new Transformation());
        trans3->Add(make_ref(new ScaleTransform(0.2)));
        trans3->Add(make_ref(new TranslateTransform(glm::vec3(0.0, -0.5, -2.0))));
        auto sphere3 = make_ref(new DrawableObject(sphereModel, trans3, shaderProgramManager.GetShaderProgram("sp")));
        AddDrawableObject(sphere3);

        auto trans4 = make_ref(new Transformation());
        trans4->Add(make_ref(new ScaleTransform(0.2)));
        trans4->Add(make_ref(new TranslateTransform(glm::vec3(-0.5, 0.0, -2.0))));
        auto sphere4 = make_ref(new DrawableObject(sphereModel, trans4, shaderProgramManager.GetShaderProgram("sp")));
        AddDrawableObject(sphere4);

        auto light = make_ref(new PointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, -2.0), 30));
        AddPointLight(light);
    }
};



class Cv6Scene5 : public Scene {
public:
    Cv6Scene5() {
        auto vertexShader = make_ref(new Shader("../assets/vs.glsl", GL_VERTEX_SHADER));
        auto fragmentShaderPhong = make_ref(new Shader("../assets/fs_phong.glsl", GL_FRAGMENT_SHADER));
        auto fragmentShaderWrong = make_ref(new Shader("../assets/fs_wrong.glsl", GL_FRAGMENT_SHADER));

        AddShaderProgram("sp_phong", make_ref(new ShaderProgram({vertexShader, fragmentShaderPhong})));
        AddShaderProgram("sp_wrong", make_ref(new ShaderProgram({vertexShader, fragmentShaderWrong})));

        auto sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        auto sphereVAO = make_ref(new VertexArray(sphereVBO));
        auto sphereModel = make_ref(new Model(sphereVAO));

        auto trans1 = make_ref(new Transformation());
        trans1->Add(make_ref(new ScaleTransform(0.2)));
        trans1->Add(make_ref(new TranslateTransform(glm::vec3(-0.3, 0.0, 0.0))));
        auto sphere1 = make_ref(new DrawableObject(sphereModel, trans1, shaderProgramManager.GetShaderProgram("sp_phong")));
        AddDrawableObject(sphere1);

        auto trans2 = make_ref(new Transformation());
        trans2->Add(make_ref(new ScaleTransform(0.2)));
        trans2->Add(make_ref(new TranslateTransform(glm::vec3(0.3, 0.0, 0.0))));
        auto sphere2 = make_ref(new DrawableObject(sphereModel, trans2, shaderProgramManager.GetShaderProgram("sp_wrong")));
        AddDrawableObject(sphere2);

        auto light = make_ref(new PointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, -1.0), 30));
        AddPointLight(light);
    }
};