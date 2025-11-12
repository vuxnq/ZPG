#include "core/Skybox.h"

#include "vendor/stb/stb_image.h"

Skybox::Skybox() {
    auto vertexShader = make_ref(new Shader("../assets/shaders/vs_skybox.glsl", GL_VERTEX_SHADER));
    auto fragmentShader = make_ref(new Shader("../assets/shaders/fs_skybox.glsl", GL_FRAGMENT_SHADER));
    shaderProgram = make_ref(new ShaderProgram({vertexShader, fragmentShader}));

    auto vertexBuffer = make_ref(new VertexBuffer(skycube, sizeof(skycube), {{ElementType::Float, 3}}));
    vertexArray = make_ref(new VertexArray(vertexBuffer));
}

void Skybox::SetSkybox(const SkyboxFaces& faces) {
    int text_width, text_height, channels;
    stbi_set_flip_vertically_on_load(false);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    unsigned char* data;
    data = stbi_load(faces.posx.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    data = stbi_load(faces.negx.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    data = stbi_load(faces.posy.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    data = stbi_load(faces.negy.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    data = stbi_load(faces.posz.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    data = stbi_load(faces.negz.c_str(), &text_width, &text_height, &channels, 4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, text_width, text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);

    shaderProgram->Use();
    shaderProgram->SetUniform("skyboxCubemap", 0);
    shaderProgram->UnUse();
}

void Skybox::Draw() {
    shaderProgram->Use();
    vertexArray->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glDrawArrays(GL_TRIANGLES, 0, 108);

    vertexArray->Unbind();
    shaderProgram->UnUse();
}
