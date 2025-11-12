#version 330

in vec3 texCoord;

uniform samplerCube skyboxCubemap;

out vec4 fragColor;

void main () {
    fragColor = texture(skyboxCubemap, texCoord);
}
