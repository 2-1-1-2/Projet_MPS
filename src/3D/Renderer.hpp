#pragma once
#include <cstdlib>
#include <vector>
#include "../Probas/Math.hpp"
#include "3D/common/TrackballCamera.hpp"
#include "3D/common/glimac/common.hpp"
#include "3D/common/glimac/sphere_vertices.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "header/helper.hpp"
#include "header/shaderProgram.hpp"

class Renderer {
private:
    std::vector<glimac::ShapeVertex> vertices     = glimac::sphere_vertices(1.f, 32, 16);
    LightProgram                     lightProgram = LightProgram("..\\src\\3D\\shaders\\3D.vs.glsl", "..\\src\\3D\\shaders\\pointLight.fs.glsl");
    VBO                              vbo;
    VAO                              vao;
    p6::Context*                     ctx;

public:
    TrackballCamera camera;
    Renderer(p6::Context* context);
    void setup();
    void draw();
    void controls();
};