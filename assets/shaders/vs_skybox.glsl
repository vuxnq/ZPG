#version 330

layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

out vec3 texCoord;

void main () {
    texCoord = vp;
    gl_Position = projMatrix * mat4(mat3(viewMatrix)) * vec4(vp, 1.0);
}
