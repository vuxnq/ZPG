#version 330

in vec4 outColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(vec3(outColor.r + outColor.g + outColor.b), outColor.a);
}
