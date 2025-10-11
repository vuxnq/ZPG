#pragma once
#include "core/Scene.h"

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


        ref<DrawableObject> bushes1 = make_ref(new DrawableObject(bushesModel, make_ref<Transformation>(), shaderProgram));
        AddDrawableObject(bushes1);
    }

private:
    ref<ShaderProgram> shaderProgram;
};