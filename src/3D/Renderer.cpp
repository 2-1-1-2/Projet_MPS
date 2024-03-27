#pragma once
#include "Renderer.hpp"
#include <iostream>
#include <vector>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

Renderer::Renderer(p6::Context* context)
{
    ctx = context;
}

// Setup what we need to do before accessing the render loop
void Renderer::setup()
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

    /* TODO: Voir si problème ici */
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
    std::vector<glm::vec3> rotationAxes;
    for (unsigned int i = 0; i < 32; i++)
    {
        rotationAxes.push_back(glm::sphericalRand(2.f));
    }
}

// Draw the elements in the render loop
void Renderer::draw()
{
    const glm::mat4 globalMVMatrix = camera.getViewMatrix();
    vao.bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    lightProgram.use();

    lightProgram.uniformText();

    const glm::mat4 earthMVMatrix =
        glm::rotate(globalMVMatrix, ctx->time(), {0.f, 5.f, 0.f});

    glm::mat4 ProjMatrix =
        glm::perspective(glm::radians(70.f), ctx->aspect_ratio(), 0.1f, 100.f);

    lightProgram.transform(ProjMatrix, earthMVMatrix, camera.getViewMatrix(), ctx->time());

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    // moonProgram.use();
    // for (unsigned int i = 0; i < 32; i++)
    // {
    //     moonProgram.uniformText();
    //     /* MOON MATRIX - TRANSFORMATION*/
    //     glm::mat4 moonMVMatrix =
    //         glm::rotate(globalMVMatrix, ctx.time() * (rotationAxes[i].x + rotationAxes[i].y + rotationAxes[i].z), {0.f, 1.f, 0.f});
    //     // Translation * Rotation
    //     moonMVMatrix = glm::translate(
    //         moonMVMatrix,
    //         rotationAxes[i]
    //     ); // Translation * Rotation * Translation
    //     moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3{0.2f});

    //     moonProgram.transform(ProjMatrix, moonMVMatrix, camera.getViewMatrix(), ctx.time());
    //     /* moon.activeTexture(); */
    //     glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //     /* moon.deactiveTexture(); */

    //     // Fix the typo here
    // }
    vao.debind();
}

// void Renderer::controls()
// {
//     ctx->mouse_scrolled = [&camera](p6::MouseScroll mouseScroll) {
//         camera.moveFront(mouseScroll.dy);
//     };
//     ctx->mouse_dragged = [&camera](p6::MouseDrag mouseMove) {
//         camera.rotateUp(mouseMove.position.x);
//         camera.rotateLeft(mouseMove.position.y);
//     };
// }