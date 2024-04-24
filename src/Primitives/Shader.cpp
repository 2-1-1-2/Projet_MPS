#include "Shader.hpp"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : ID(shader.id()), shader{p6::load_shader("assets/shaders/" + vertexShaderPath, "assets/shaders/" + fragmentShaderPath)}, uVMatrix(glGetUniformLocation(ID, "uVMatrix")), uMMatrix(glGetUniformLocation(ID, "uMMatrix")), uMVPMatrix(glGetUniformLocation(ID, "uMVPMatrix")), uMVMatrix(glGetUniformLocation(ID, "uMVMatrix")), uNormalMatrix(glGetUniformLocation(ID, "uNormalMatrix")), uTexture(glGetUniformLocation(ID, "uTexture")), uKd(glGetUniformLocation(ID, "uKd")), uKs(glGetUniformLocation(ID, "uKs")), uShininess(glGetUniformLocation(ID, "uShininess")), uTransparency(glGetUniformLocation(ID, "uTransparency")), uLightDir_vs(glGetUniformLocation(ID, "uLightDir_vs")), uLightPos_vs(glGetUniformLocation(ID, "uLightPos_vs")), uLightIntensity(glGetUniformLocation(ID, "uLightIntensity"))
{
}