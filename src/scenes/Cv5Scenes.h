#pragma once
#include "core/Scene.h"
#include <random>

#include "assets/vertices/bushes.h"
#include "assets/vertices/plain.h"
#include "assets/vertices/tree.h"
#include "assets/vertices/sphere.h"

class Cv5Scene1 : public Scene {
public:
    Cv5Scene1() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/shaders/cv5/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/shaders/cv5/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<ShaderProgram> shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));
        shaderProgramManager.AddShaderProgram("sp", shaderProgram);

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp").get());

        float points_triangle[] = {
            // pos              // normal
            0.0f, 0.5f, -1.0f,   1.f, 0.f, 0.f,
            0.5f, -0.5f, -1.0f,  0.f, 1.f, 0.f,
            -0.5f, -0.5f, -1.0f, 0.f, 0.f, 1.f,
        };

        ref<VertexBuffer> triangleVBO = make_ref(new VertexBuffer(points_triangle, sizeof(points_triangle)));
        triangleVBO->SetLayout({
            {ElementType::Float, 3},
            {ElementType::Float, 3}
        });
        ref<VertexArray> triangleVAO = make_ref(new VertexArray(triangleVBO));
        ref<Model> triangleModel = make_ref(new Model(triangleVAO));
        ref<DrawableObject> triangleObject = make_ref(new DrawableObject(
            triangleModel,
            make_ref(new Transformation()),
            shaderProgramManager.GetShaderProgram("sp")
        ));

        AddDrawableObject(triangleObject);

        auto pointLight1 = make_ref(new PointLight(glm::vec3(0.385, 0.647, 0.812), glm::vec3(10.0f, 10.0f, 10.0f), {}));
        AddLight(pointLight1);
    }
};



class Cv5Scene2 : public Scene {
public:
    Cv5Scene2() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/shaders/cv5/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/shaders/cv5/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<ShaderProgram> shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));
        shaderProgramManager.AddShaderProgram("sp", shaderProgram);

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp").get());

        ref<VertexBuffer> sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> sphereVAO = make_ref(new VertexArray(sphereVBO));
        ref<Model> sphereModel = make_ref(new Model(sphereVAO));
        auto so1T = make_ref(new Transformation());
        so1T->Add(make_ref(new ScaleTransform(0.2)));
        so1T->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.5f, 0.0f))));
        auto so2T = make_ref(new Transformation());
        so2T->Add(make_ref(new ScaleTransform(0.2)));
        so2T->Add(make_ref(new TranslateTransform(glm::vec3(0.5f, 0.0f, 0.0f))));
        auto so3T = make_ref(new Transformation());
        so3T->Add(make_ref(new ScaleTransform(0.2)));
        so3T->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, -0.5f, 0.0f))));
        auto so4T = make_ref(new Transformation());
        so4T->Add(make_ref(new ScaleTransform(0.2)));
        so4T->Add(make_ref(new TranslateTransform(glm::vec3(-0.5f, 0.0f, 0.0f))));
        ref<DrawableObject> sphereObject1 = make_ref(new DrawableObject(sphereModel, so1T, shaderProgram));
        ref<DrawableObject> sphereObject2 = make_ref(new DrawableObject(sphereModel, so2T, shaderProgram));
        ref<DrawableObject> sphereObject3 = make_ref(new DrawableObject(sphereModel, so3T, shaderProgram));
        ref<DrawableObject> sphereObject4 = make_ref(new DrawableObject(sphereModel, so4T, shaderProgram));

        AddDrawableObject(sphereObject1);
        AddDrawableObject(sphereObject2);
        AddDrawableObject(sphereObject3);
        AddDrawableObject(sphereObject4);

        auto pointLight1 = make_ref(new PointLight(glm::vec3(0.385, 0.647, 0.812), glm::vec3(0.0f, 0.0f, 0.0f), {}));
        AddLight(pointLight1);
    }
};



class Cv5Scene3 : public Scene {
public:
    Cv5Scene3() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/shaders/cv5/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/shaders/cv5/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<ShaderProgram> shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));
        shaderProgramManager.AddShaderProgram("sp", shaderProgram);

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp").get());

        ref<VertexBuffer> bushesVBO = make_ref(new VertexBuffer(bushes, sizeof(bushes), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> bushesVAO = make_ref(new VertexArray(bushesVBO));
        ref<Model> bushesModel = make_ref(new Model(bushesVAO));

        ref<VertexBuffer> treeVBO = make_ref(new VertexBuffer(tree, sizeof(tree), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> treeVAO = make_ref(new VertexArray(treeVBO));
        ref<Model> treeModel = make_ref(new Model(treeVAO));

        ref<VertexBuffer> plainVBO = make_ref(new VertexBuffer(plain, sizeof(plain), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> plainVAO = make_ref(new VertexArray(plainVBO));
        ref<Model> plainModel = make_ref(new Model(plainVAO));

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> rTreeOffset(-plainSize, plainSize);
        std::uniform_real_distribution<float> rBushesOffsetRelativeToTreeOffset(-0.5f, 0.5f);
        std::uniform_real_distribution<float> rAngle(0.0f, 360.0f);
        std::uniform_real_distribution<float> rScale(0.6f, 1.0f);

        // trees
        for (int i = 0; i < treeCount; i++) {
            auto treeTransform = make_ref(new Transformation());
            treeTransform->Add(make_ref(new ScaleTransform(rScale(gen))));
            treeTransform->Add(make_ref(new RotateTransform(rAngle(gen), glm::vec3(0.0f, 1.0f, 0.0f))));
            treeTransform->Add(make_ref(new TranslateTransform(glm::vec3(rTreeOffset(gen), 0.0f, rTreeOffset(gen)))));
            ref<DrawableObject> treeObject = make_ref(new DrawableObject(treeModel, treeTransform, shaderProgram));

            // bushes around the tree
            for (int j = 0; j < 10; j++) {
                if (rand() % 2) continue;

                auto bushesTransform = make_ref(new Transformation());
                bushesTransform->Add(make_ref(new ScaleTransform(rScale(gen))));
                bushesTransform->Add(make_ref(new RotateTransform(rAngle(gen), glm::vec3(0.0f, 1.0f, 0.0f))));
                bushesTransform->Add(make_ref(new TranslateTransform(glm::vec3(rBushesOffsetRelativeToTreeOffset(gen), 0.0f, rBushesOffsetRelativeToTreeOffset(gen)))));
                bushesTransform->Add(treeTransform);
                ref<DrawableObject> bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgram));
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
            ref<DrawableObject> bushesObject = make_ref(new DrawableObject(bushesModel, bushesTransform, shaderProgram));
            AddDrawableObject(bushesObject);
        }

        ref<DrawableObject> plainObject = make_ref(new DrawableObject(plainModel, make_ref(new ScaleTransform(plainSize)), shaderProgram));
        AddDrawableObject(plainObject);

        auto pointLight1 = make_ref(new PointLight(glm::vec3(0.385, 0.647, 0.812), glm::vec3(10.0f, 10.0f, 10.0f), {}));
        AddLight(pointLight1);
    }

private:
    float plainSize = 10.0f;
    int bushesDensity = 4;
    int treeCount = 50;
};



class Cv5Scene4 : public Scene {
public:
    Cv5Scene4() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/shaders/cv5/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/shaders/cv5/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderConstantSun = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_constant_sun.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderLambert = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_lambert.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderPhong = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_phong.glsl", GL_FRAGMENT_SHADER));
        shaderProgramManager.AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        shaderProgramManager.AddShaderProgram("sp_constant", make_ref(new ShaderProgram({vertexShader, fragmentShaderConstantSun})));
        shaderProgramManager.AddShaderProgram("sp_lambert", make_ref(new ShaderProgram({vertexShader, fragmentShaderLambert})));
        shaderProgramManager.AddShaderProgram("sp_phong", make_ref(new ShaderProgram({vertexShader, fragmentShaderPhong})));

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_constant").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_lambert").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_phong").get());

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
        auto moonObject = make_ref(new DrawableObject(sphereModel, moonTransform, shaderProgramManager.GetShaderProgram("sp")));

        AddDrawableObject(sunObject);
        AddDrawableObject(earthObject);
        AddDrawableObject(moonObject);

        auto sunPointLight = make_ref(new PointLight(glm::vec3(1.0, 1.0, 0.9), glm::vec3(0.0, 0.0, 0.0), {}));
        AddLight(sunPointLight);
    }
};



class Cv5Scene5 : public Scene {
public:
    Cv5Scene5() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/shaders/cv5/vertex_shader.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/shaders/cv5/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderConstant = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_constant.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderLambert = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_lambert.glsl", GL_FRAGMENT_SHADER));
        ref<Shader> fragmentShaderPhong = make_ref(new Shader("../assets/shaders/cv5/fragment_shader_phong.glsl", GL_FRAGMENT_SHADER));

        shaderProgramManager.AddShaderProgram("sp", make_ref(new ShaderProgram({vertexShader, fragmentShader})));
        shaderProgramManager.AddShaderProgram("sp_constant", make_ref(new ShaderProgram({vertexShader, fragmentShaderConstant})));
        shaderProgramManager.AddShaderProgram("sp_lambert", make_ref(new ShaderProgram({vertexShader, fragmentShaderLambert})));
        shaderProgramManager.AddShaderProgram("sp_phong", make_ref(new ShaderProgram({vertexShader, fragmentShaderPhong})));

        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_constant").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_lambert").get());
        camera.AddSubscriber(shaderProgramManager.GetShaderProgram("sp_phong").get());

        ref<VertexBuffer> sphereVBO = make_ref(new VertexBuffer(sphere, sizeof(sphere), {{ElementType::Float, 3}, {ElementType::Float, 3}}));
        ref<VertexArray> sphereVAO = make_ref(new VertexArray(sphereVBO));
        ref<Model> sphereModel = make_ref(new Model(sphereVAO));
        auto so1T = make_ref(new Transformation());
        so1T->Add(make_ref(new ScaleTransform(0.2)));
        so1T->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, 0.5f, 0.0f))));
        auto so2T = make_ref(new Transformation());
        so2T->Add(make_ref(new ScaleTransform(0.2)));
        so2T->Add(make_ref(new TranslateTransform(glm::vec3(0.5f, 0.0f, 0.0f))));
        auto so3T = make_ref(new Transformation());
        so3T->Add(make_ref(new ScaleTransform(0.2)));
        so3T->Add(make_ref(new TranslateTransform(glm::vec3(0.0f, -0.5f, 0.0f))));
        auto so4T = make_ref(new Transformation());
        so4T->Add(make_ref(new ScaleTransform(0.2)));
        so4T->Add(make_ref(new TranslateTransform(glm::vec3(-0.5f, 0.0f, 0.0f))));
        ref<DrawableObject> sphereObject1 = make_ref(new DrawableObject(sphereModel, so1T, shaderProgramManager.GetShaderProgram("sp_constant")));
        ref<DrawableObject> sphereObject2 = make_ref(new DrawableObject(sphereModel, so2T, shaderProgramManager.GetShaderProgram("sp_lambert")));
        ref<DrawableObject> sphereObject3 = make_ref(new DrawableObject(sphereModel, so3T, shaderProgramManager.GetShaderProgram("sp_phong")));
        ref<DrawableObject> sphereObject4 = make_ref(new DrawableObject(sphereModel, so4T, shaderProgramManager.GetShaderProgram("sp")));

        AddDrawableObject(sphereObject1);
        AddDrawableObject(sphereObject2);
        AddDrawableObject(sphereObject3);
        AddDrawableObject(sphereObject4);

        auto pointLight1 = make_ref(new PointLight(glm::vec3(0.385, 0.647, 0.812), glm::vec3(0.0f, 0.0f, 0.0f), {}));
        AddLight(pointLight1);
    }
};
