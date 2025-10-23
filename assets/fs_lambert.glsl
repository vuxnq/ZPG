#version 330

struct PointLight {
    vec3 position;
    vec3 color;
    int intensity;
};
#define MAX_POINTLIGHTS 10
uniform PointLight pointLights[MAX_POINTLIGHTS];
uniform int pointLightCount;

uniform vec3 cameraPos;

in vec4 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

vec3 calculatePointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    return diff * light.color;
}

void main(void) {
    vec3 fragPos = vec3(worldPos);
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPos - fragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < pointLightCount; i++) {
        result += calculatePointLight(pointLights[i], fragPos, normal, viewDir);
    }

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + vec4(result, 1.0);
}