#version 330

uniform vec3 cameraPos;

uniform sampler2D diffuseTexture;
uniform bool useDiffuseTexture;

in vec3 worldPos;
in vec3 worldNormal;
in vec2 texCoord;

out vec4 fragColor;

void main(void) {
    vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
    fragColor = ambient * texture(diffuseTexture, texCoord);
}