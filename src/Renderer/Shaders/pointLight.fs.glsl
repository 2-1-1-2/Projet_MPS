#version 330

in vec2 vTexCoords;
in vec3 vPosition_vs; // Position du sommet transformée dans l'espace View (vs)
in vec3 vNormal_vs; // Normale du sommet transformée dans l'espace View (vs)

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;
out vec4 fFragColor;

vec3 ponctuel() {
    vec3 w_i = normalize(uLightPos_vs - vPosition_vs);
    float d = distance(uLightPos_vs, vPosition_vs);
    float d_2 = d * d;
    vec3 L_i = (uLightIntensity / d_2);
    vec3 w_0 = normalize(-vPosition_vs);
    vec3 halfV = (w_0 + w_i) / 2.;
    float dot_1 = (dot(w_i, normalize(vNormal_vs)));
    float dot_2 = (dot(halfV, normalize(vNormal_vs)));

    return L_i * (uKd * dot_1) + uKs * pow(dot_2, uShininess);
}

void main() {
    /* vec3 normalizedNormal = normalize(vNormal_vs);
     */
    fFragColor = vec4(ponctuel(), 1.);
}