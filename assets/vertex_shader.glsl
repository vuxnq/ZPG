#version 330

layout(location = 0) in vec3 vp;
layout(location = 1) in vec4 color;

uniform mat4 modelMatrix;
// uniform mat4 viewMatrix;

out vec4 outColor;

void main() {
    // gl_Position = viewMatrix * modelMatrix * vec4(vp, 1.0);
    gl_Position = modelMatrix * vec4(vp, 1.0);
    outColor = color;
}