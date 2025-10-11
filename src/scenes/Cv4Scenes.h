#pragma once
#include "core/Scene.h"
#include <random>

#include "assets/models/bushes.h"
#include "assets/models/plain.h"
#include "assets/models/tree.h"

class Cv4Scene : public Scene {
public:
    Cv4Scene() {
        ref<Shader> vertexShader = make_ref(new Shader("../assets/vertex_shader_normal.glsl", GL_VERTEX_SHADER));
        ref<Shader> fragmentShader = make_ref(new Shader("../assets/fragment_shader.glsl", GL_FRAGMENT_SHADER));
        shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

        camera.AddSubscriber(shaderProgram);

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
    }

private:
    ref<ShaderProgram> shaderProgram;
    float plainSize = 10.0f;
    int bushesDensity = 4;
    int treeCount = 50;
};