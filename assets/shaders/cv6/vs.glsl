#version 330

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec4 worldPos;
out vec3 worldNormal;

void main() {
    worldPos = modelMatrix * vec4(vp, 1.0);
    gl_Position = projMatrix * viewMatrix * worldPos;
    worldNormal = mat3(transpose(inverse(modelMatrix))) * vn;
}
