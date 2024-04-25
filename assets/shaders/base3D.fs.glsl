#version 330

struct PointLight {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

in vec2 vTexCoords;
in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec3 vViewMatrix;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform float uTransparency;

uniform sampler2D uTexture;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform PointLight pointLights[2];

out vec4 fFragColor;

vec3 blinnPhongDirectionalLight() {
    vec3 w_i = normalize(uLightDir_vs);
    vec3 L_i = uLightIntensity;
    vec3 w_0 = normalize(-vPosition_vs);
    vec3 halfV = normalize(w_0 + w_i);
    float dot_1 = max(dot(normalize(-vNormal_vs), w_i), 0.0);
    float dot_2 = pow(max(dot(normalize(-vNormal_vs), halfV), 0.0), uShininess);

    return L_i * (uKd * dot_1 + uKs * dot_2);
}

vec3 pointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    vec3 ambient = 0.1 * light.color;
    vec3 diffuse = diff * light.color;
    vec3 specular = spec * light.color;
    return (ambient + diffuse + specular) * attenuation;
}

void main() {
    vec3 normal = normalize(vNormal_vs);
    vec3 light = blinnPhongDirectionalLight();

    // Calculate and accumulate lighting from point lights
    for (int i = 0; i < pointLights.length(); i++) {
        light += pointLight(pointLights[i], normal, vPosition_vs);
    }

    // Apply texture
    vec4 textureColor = texture(uTexture, vTexCoords);
    fFragColor = vec4(light, 1.0) * textureColor;

    // Apply transparency
    fFragColor.a *= uTransparency;
}