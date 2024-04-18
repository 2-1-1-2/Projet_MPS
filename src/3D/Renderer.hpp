#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../Probas/Math.hpp"
#include "3D/common/TrackballCamera.hpp"
#include "3D/common/glimac/box_vertices.hpp"
#include "3D/common/glimac/common.hpp"
#include "3D/common/glimac/sphere_vertices.hpp"
#include "Renderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "header/helper.hpp"
#include "header/shaderProgram.hpp"
#include "p6/p6.h"


class Renderer {
protected:
    std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);
    VBO                              vbo;
    VAO                              vao;
    p6::Context*                     ctx;
    ShaderProgram*                   m_sp;
    glm::mat4                        mvMatrix{};

public:
    void setMVMatrix(const glm::mat4& MVM)
    {
        mvMatrix = MVM;
    }
    void setVertices(const std::vector<glimac::ShapeVertex>& v)
    {
        vertices = v;
    }
    void draw(const TrackballCamera& camera)
    {
        vao.bind();

        m_sp->use();

        m_sp->uniformText();

        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), ctx->aspect_ratio(), 0.1f, 100.f);

        m_sp->transform(ProjMatrix, mvMatrix, camera.getViewMatrix(), ctx->time());

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        vao.debind();
    }

    Renderer(p6::Context* context, ShaderProgram* sp)
        : ctx(context), m_sp(sp) {}

    // Setup what we need to do before accessing the render loop
    void setup()
    {
        vbo.bind();
        vbo.bufferData(vertices);
        vbo.debind();

        vao.bind();

        /* activer les attributs */
        static constexpr GLuint aVertexPosition  = 0;
        static constexpr GLuint aVertexNormal    = 1;
        static constexpr GLuint aVertexTexCoords = 2;
        glEnableVertexAttribArray(aVertexPosition);
        glEnableVertexAttribArray(aVertexNormal);
        glEnableVertexAttribArray(aVertexTexCoords);

        vbo.bind();
        glVertexAttribPointer(
            aVertexPosition, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
            (const GLvoid*)(offsetof(glimac::ShapeVertex, position))
        );
        glVertexAttribPointer(
            aVertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
            (const GLvoid*)(offsetof(glimac::ShapeVertex, normal))
        );
        glVertexAttribPointer(
            aVertexTexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
            (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords))
        );

        vbo.debind();
        vao.debind();
    }
};
