#version 330

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

void main() {
    vec3 color = texture(uTexture, vTexCoords).rgb;
    color *= uLightIntensity; // Modulation par l'intensité de la lumière
    fFragColor = vec4(color, 1.0);
}