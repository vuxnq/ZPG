#version 330

struct LightAttenuation {
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float intensity;
};

struct PointLight {
    vec3 color;
    vec3 position;
    LightAttenuation attenuation;
};

struct SpotLight {
    vec3 color;
    vec3 position;
    vec3 direction;
    LightAttenuation attenuation;
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

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 cameraPos;

uniform Material material;

uniform sampler2D textureUnitId;

in vec3 worldPos;
in vec3 worldNormal;
in vec2 texCoord;

out vec4 fragColor;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // specular - blinn-phong
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), material.shininess);

    if (dot(normal, lightDir) < 0.0) spec = 0;

    return (diff * material.diffuse + spec * material.specular) * light.color * light.intensity;
}

vec3 calculatePointLight(PointLight light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(lightDir, normal), 0.0);

    // specular - phong
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);

    // specular - blinn-phong
    vec3 halfway = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfway), 0.0), material.shininess);

    if (dot(normal, lightDir) < 0.0) spec = 0;

    // attenuation
    float dist = length(light.position - fragPos);
    LightAttenuation a = light.attenuation;
    float attenuation = a.intensity / (a.constant + a.linear * dist + a.quadratic * dist * dist);
    attenuation = clamp(attenuation, 0.0 , 1.0);

    return (diff * material.diffuse + spec * material.specular) * attenuation * light.color;
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
    float spec = pow(max(dot(normal, halfway), 0.0), material.shininess);

    if (dot(normal, lightDir) < 0.0) spec = 0;

    // attenuation
    float dist = length(light.position - fragPos);
    LightAttenuation a = light.attenuation;
    float attenuation = a.intensity / (a.constant + a.linear * dist + a.quadratic * dist * dist);
    attenuation = clamp(attenuation, 0.0 , 1.0);

    return (diff * material.diffuse + spec * material.specular) * attenuation * intens * light.color;
}

void main(void) {
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(cameraPos - worldPos);

    vec3 result = vec3(0.0);

    for (int i = 0; i < directionalLightCount; i++) {
        result += calculateDirectionalLight(directionalLights[i], worldPos, normal, viewDir);
    }

    for (int i = 0; i < pointLightCount; i++) {
        result += calculatePointLight(pointLights[i], worldPos, normal, viewDir);
    }

    for (int i = 0; i < spotLightCount; i++) {
        result += calculateSpotLight(spotLights[i], worldPos, normal, viewDir);
    }

    fragColor = vec4((ambient * material.ambient), 1.0) + vec4(result, 1.0);
    // fragColor = texture(textureUnitId, texCoord);
}