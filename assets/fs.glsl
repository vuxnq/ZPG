#version 330

struct DirectionalLight {
    vec3 color;
    vec3 direction;
    int intensity;
};

struct PointLight {
    vec3 color;
    vec3 position;
    int intensity;
};

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    int intensity;
};

#define MAX_DIRECTIONALLIGHTS 10
#define MAX_POINTLIGHTS 100
#define MAX_SPOTLIGHTS 100

uniform vec3 ambient;

uniform DirectionalLight directionalLights[MAX_DIRECTIONALLIGHTS];
uniform int directionalLightCount;

uniform PointLight pointLights[MAX_POINTLIGHTS];
uniform int pointLightCount;

uniform SpotLight spotLights[MAX_SPOTLIGHTS];
uniform int spotLightCount;

uniform vec3 cameraPos;

in vec4 worldPos;
in vec3 worldNormal;

out vec4 fragColor;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // specular - blinn-phong
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 32.0);

    return (diff + spec) * light.color * (light.intensity / 10.0);
}

vec3 calculatePointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // specular - phong
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    // specular - blinn-phong
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 32.0);

    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = light.intensity / ((dist * dist * 10) + light.intensity);

    return (diff + spec) * attenuation * light.color;
}

vec3 calculateSpotLight(SpotLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // cutoff
    float theta = dot(lightDir, normalize(-light.direction));

    // cutoff - soft edges
    float innerCutOff = cos(radians(30));
    float outerCutOff = cos(radians(45));
    float intens = (theta - outerCutOff) / (innerCutOff - outerCutOff);
    intens = clamp(intens, 0.0, 1.0);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // specular - blinn-phong
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), 32.0);

    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = light.intensity / ((dist * dist * 10) + light.intensity);

    return (diff + spec) * attenuation * intens * light.color;
}

void main(void) {
    vec3 fragPos = vec3(worldPos);
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPos - fragPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < directionalLightCount; i++) {
        result += calculateDirectionalLight(directionalLights[i], fragPos, normal, viewDir);
    }

    for (int i = 0; i < pointLightCount; i++) {
        result += calculatePointLight(pointLights[i], fragPos, normal, viewDir);
    }

    for (int i = 0; i < spotLightCount; i++) {
        result += calculateSpotLight(spotLights[i], fragPos, normal, viewDir);
    }

    // vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0);
    fragColor = vec4(ambient, 1.0) + vec4(result, 1.0);
}