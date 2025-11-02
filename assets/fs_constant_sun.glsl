#version 330

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

#define MAX_POINTLIGHTS 100
uniform PointLight pointLights[MAX_POINTLIGHTS];
uniform int pointLightCount;

uniform vec3 cameraPos;

in vec3 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

void main(void) {
    vec4 ambient = vec4(1.0, 1.0, 0.5, 1.0);
    fragColor = ambient;
}