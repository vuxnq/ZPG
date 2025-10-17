#version 330

struct PointLight {
    vec3 position;
    vec3 color;
};
#define MAX_POINTLIGHTS 10
uniform PointLight pointLights[MAX_POINTLIGHTS];

uniform vec3 cameraPos;

in vec4 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

void main(void) {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    fragColor = ambient;
}