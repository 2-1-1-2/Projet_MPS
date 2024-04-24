#pragma once
#include "p6/p6.h"

class Shader {
public:
    // Shader program
    p6::Shader shader;
    GLint      ID;

    // Uniform locations in the shader program
    GLint uVMatrix;
    GLint uMMatrix;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uTransparency;
    GLint uLightDir_vs;
    GLint uLightPos_vs;
    GLint uLightIntensity;

    // Constructor initializes shader with paths to vertex and fragment shader source files, default to basic shaders
    explicit Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
};