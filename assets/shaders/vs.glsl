#version 330

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 tc;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec3 worldPos;
out vec3 worldNormal;
out vec2 texCoord;

void main() {
    vec4 wPos4 = modelMatrix * vec4(vp, 1.0);
    // TODO: w
    worldPos = wPos4.xyz;
    worldNormal = mat3(transpose(inverse(modelMatrix))) * vn;
    texCoord = tc;
    gl_Position = projMatrix * viewMatrix * wPos4;
}
