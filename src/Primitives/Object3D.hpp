#pragma once
#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "p6/p6.h"

// Manages a 3D object including its model, texture, shader, and OpenGL buffer objects
class Object3D {
private:
    Model   _model;
    Texture _texture;
    Shader  _shader;

    GLuint _vbo{};
    GLuint _vao{};

public:
    explicit Object3D(const std::string& name = "BoundingCube", const std::string& vertexShaderPath = "3D.vs.glsl", const std::string& fragmentShaderPath = "tex3D.fs.glsl");
    explicit Object3D(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& skinID, const std::string& lodID);

    void defineVBO();
    void defineVAO();

    std::vector<glimac::ShapeVertex> getMesh() const { return _model.getVertices(); };
    GLuint                           getVAO() const { return _vao; };
    const Model&                     getModel() const { return _model; };
    const Texture&                   getTexture() const { return _texture; };
    const Shader&                    getShader() const { return _shader; };

    // Cleans up the resources
    void clear();
};