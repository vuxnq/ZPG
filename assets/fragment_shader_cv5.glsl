#version 330


struct PointLight {
    vec3 position;
    vec3 color;
};


in vec4 outColor;
in vec4 worldPosition;
in vec3 worldNormal;

out vec4 fragColor;


#define MAX_LIGHTS 10
uniform PointLight pointLights[MAX_LIGHTS];

vec3 calculatePointLight(PointLight light, vec3 fragPos, vec3 normal) {
    vec3 lightDirection = light.position - fragPos;
    float diffusion = max(dot(normalize(lightDirection), normalize(normal)), 0.0);
    return diffusion * light.color;
}


void main(void) {

    vec3 result = vec3(0.0);
    for (int i = 0; i < MAX_LIGHTS; i++) {
        result += calculatePointLight(pointLights[i], vec3(worldPosition), worldNormal);
    }


    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + vec4(result, 1.0);
}