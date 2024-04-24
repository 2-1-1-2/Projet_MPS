#version 330

in vec2 vTexCoords;
in vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
in vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)

out vec4 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform float uTransparency;

uniform sampler2D uTexture;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


vec3 blinnPhong() {
    vec3 w_i = normalize(uLightDir_vs);
    vec3 L_i = uLightIntensity;
    vec3 w_0 = normalize(-vPosition_vs);
    vec3 halfV = (w_0 + w_i) / 2.;
    float dot_1 = (dot(w_i, normalize(vNormal_vs)));
    float dot_2 = (dot(halfV, normalize(vNormal_vs)));

    return L_i * (uKd * dot_1) + uKs * pow(dot_2, uShininess);
}

void main() {
    vec4 texture1 = texture(uTexture, vTexCoords);
    fFragColor = texture1 * vec4(blinnPhong(), 1.) * uTransparency;
}