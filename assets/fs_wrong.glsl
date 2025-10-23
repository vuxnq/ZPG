#version 330

struct PointLight {
    vec3 position;
    vec3 color;
    int intensity;
};
#define MAX_POINTLIGHTS 100
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

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

    if (dot(normal, lightDir) < 0.0) {
        reflectDir = vec3(0.0, 0.0, 0.0);
    }

    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = light.intensity / ((dist * dist * 10) + light.intensity);

    return (diff * light.color + spec * light.color) * attenuation;
}

void main(void) {
    vec3 fragPos = vec3(worldPos);
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPos - fragPos);

    vec3 result = vec3(0.0);
    for (int i = 0; i < pointLightCount; i++) {
        result += calculatePointLight(pointLights[i], fragPos, normal, viewDir);
    }

    vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0);
    fragColor = ambient + vec4(result, 1.0);
}