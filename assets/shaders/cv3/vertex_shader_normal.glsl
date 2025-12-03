#version 330

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;

out vec4 outColor;

void main() {
    gl_Position = modelMatrix * vec4(vp, 1.0);
    outColor = vec4(normal, 1.0);
}