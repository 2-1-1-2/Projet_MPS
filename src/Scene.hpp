#pragma once
#include <vector>
#include "Boids/Flock.hpp"
#include "Cameras/TrackballCamera.hpp"
#include "Renderer/Renderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Scene {
    /*
    - Taille de la scene
    - Position de la scene
    */

private:
    int sceneSize = 10.f;

    p6::Context ctx = p6::Context{{.title = "Projet_MPS"}}; // plutôt à mettre dans le main et à passer en parametre ?

    std::vector<Flock> flocks;
    TrackballCamera    camera;

    // Renderers
    Renderer rPlayer       = Renderer(&ctx, new LightProgram("../src/Renderer/Shaders/3D.vs.glsl", "../src/Renderer/Shaders/pointLight.fs.glsl"));
    Renderer rBoundaryCube = Renderer(&ctx, new LightProgram("../src/Renderer/Shaders/3D.vs.glsl", "../src/Renderer/Shaders/pointLight.fs.glsl"));
    Renderer rBoids        = Renderer(&ctx, new LightProgram("../src/Renderer/Shaders/3D.vs.glsl", "../src/Renderer/Shaders/pointLight.fs.glsl"));

    // std::vector<glimac::ShapeVertex> cube_vertices(float size)
    // {
    //     std::vector<glimac::ShapeVertex> vertices;

    //     // Half the size to center the cube at the origin
    //     float halfSize = size / 2.0f;

    //     // Define positions for each corner of the cube
    //     glm::vec3 positions[] = {
    //         {-halfSize, -halfSize, halfSize},  // Front-bottom-left
    //         {halfSize, -halfSize, halfSize},   // Front-bottom-right
    //         {halfSize, halfSize, halfSize},    // Front-top-right
    //         {-halfSize, halfSize, halfSize},   // Front-top-left
    //         {-halfSize, -halfSize, -halfSize}, // Back-bottom-left
    //         {halfSize, -halfSize, -halfSize},  // Back-bottom-right
    //         {halfSize, halfSize, -halfSize},   // Back-top-right
    //         {-halfSize, halfSize, -halfSize}   // Back-top-left
    //     };

    //     // Indices for constructing faces with two triangles each
    //     unsigned int indices[] = {
    //         // Front face
    //         0, 1, 2, 2, 3, 0,
    //         // Right face
    //         1, 5, 6, 6, 2, 1,
    //         // Back face
    //         5, 4, 7, 7, 6, 5,
    //         // Left face
    //         4, 0, 3, 3, 7, 4,
    //         // Top face
    //         3, 2, 6, 6, 7, 3,
    //         // Bottom face
    //         4, 5, 1, 1, 0, 4
    //     };

    //     // Define normals for each face (assuming each face has the same normal for all its vertices)
    //     glm::vec3 normals[] = {
    //         {0, 0, 1},  // Front face
    //         {1, 0, 0},  // Right face
    //         {0, 0, -1}, // Back face
    //         {-1, 0, 0}, // Left face
    //         {0, 1, 0},  // Top face
    //         {0, -1, 0}  // Bottom face
    //     };

    //     // Define texture coordinates
    //     glm::vec2 texCoords[] = {
    //         {0.0f, 0.0f},
    //         {1.0f, 0.0f},
    //         {1.0f, 1.0f},
    //         {0.0f, 1.0f}
    //     };

    //     // Create each face using the above information
    //     for (int face = 0; face < 6; ++face)
    //     {
    //         int normIndex = face; // Each face has a unique normal index
    //         for (int i = 0; i < 6; ++i)
    //         { // Each face is made of two triangles (6 vertices)
    //             int                 index = indices[face * 6 + i];
    //             glimac::ShapeVertex vertex;
    //             vertex.position  = positions[index];
    //             vertex.normal    = normals[normIndex];
    //             vertex.texCoords = texCoords[i % 4]; // Repeat texture coordinates for each vertex
    //             vertices.push_back(vertex);
    //         }
    //     }

    //     float width  = 5.0f;
    //     float height = 5.0f;
    //     float depth  = 10.0f;
    //     vertices     = {{{-width / 2, -height / 2, depth / 2}, {0, 0, 1}, {0, 0}, {1, 1, 1}}, {{width / 2, -height / 2, depth / 2}, {0, 0, 1}, {1, 0}, {1, 1, 1}}, {{width / 2, height / 2, depth / 2}, {0, 0, 1}, {1, 1}, {1, 1, 1}}, {{-width / 2, height / 2, depth / 2}, {0, 0, 1}, {0, 1}, {1, 1, 1}}, {{width / 2, -height / 2, depth / 2}, {1, 0, 0}, {0, 0}, {1, 1, 1}}, {{width / 2, -height / 2, -depth / 2}, {1, 0, 0}, {1, 0}, {1, 1, 1}}, {{width / 2, height / 2, -depth / 2}, {1, 0, 0}, {1, 1}, {1, 1, 1}}, {{width / 2, height / 2, depth / 2}, {1, 0, 0}, {0, 1}, {1, 1, 1}}, {{width / 2, -height / 2, -depth / 2}, {0, 0, -1}, {0, 0}, {1, 1, 1}}, {{-width / 2, -height / 2, -depth / 2}, {0, 0, -1}, {1, 0}, {1, 1, 1}}, {{-width / 2, height / 2, -depth / 2}, {0, 0, -1}, {1, 1}, {1, 1, 1}}, {{width / 2, height / 2, -depth / 2}, {0, 0, -1}, {0, 1}, {1, 1, 1}}, {{-width / 2, -height / 2, -depth / 2}, {-1, 0, 0}, {0, 0}, {1, 1, 1}}, {{-width / 2, -height / 2, depth / 2}, {-1, 0, 0}, {1, 0}, {1, 1, 1}}, {{-width / 2, height / 2, depth / 2}, {-1, 0, 0}, {1, 1}, {1, 1, 1}}, {{-width / 2, height / 2, -depth / 2}, {-1, 0, 0}, {0, 1}, {1, 1, 1}}, {{-width / 2, height / 2, depth / 2}, {0, 1, 0}, {0, 0}, {1, 1, 1}}, {{width / 2, height / 2, depth / 2}, {0, 1, 0}, {1, 0}, {1, 1, 1}}, {{width / 2, height / 2, -depth / 2}, {0, 1, 0}, {1, 1}, {1, 1, 1}}, {{-width / 2, height / 2, -depth / 2}, {0, 1, 0}, {0, 1}, {1, 1, 1}}, {{-width / 2, -height / 2, -depth / 2}, {0, -1, 0}, {0, 0}, {1, 1, 1}}, {{width / 2, -height / 2, -depth / 2}, {0, -1, 0}, {1, 0}, {1, 1, 1}}, {{width / 2, -height / 2, depth / 2}, {0, -1, 0}, {1, 1}, {1, 1, 1}}, {{-width / 2, -height / 2, depth / 2}, {0, -1, 0}, {0, 1}, {1, 1, 1}}},
    //     {{0, 1, 2},
    //      {2, 3, 0},
    //      {4, 5, 6},
    //      {6, 7, 4},
    //      {8, 9, 10},
    //      {10, 11, 8},
    //      {12, 13, 14},
    //      {14, 15, 12},
    //      {16, 17, 18},
    //      {18, 19, 16},
    //      {20, 21, 22},
    //      {22, 23, 20}},
    //     {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    //     return vertices;
    // }

public:
    explicit Scene(int nb_boids, int nb_flocks)

    {
        ctx.maximize_window();
        rBoundaryCube.setup();
        rPlayer.setup();
        rBoids.setup();

        // TODO: Faire un cube
        // setupBoundaryCube();

        std::vector<glimac::ShapeVertex> vtxCharacter    = glimac::sphere_vertices(1.f, 32, 16);
        std::vector<glimac::ShapeVertex> vtxBoundaryCube = glimac::box_vertices(5.f, 10.f, 7.f);

        rPlayer.setVertices(vtxCharacter);
        rBoundaryCube.setVertices(vtxBoundaryCube);

        for (unsigned int i = 0; i < nb_flocks; i++)
        {
            flocks.push_back(Flock(nb_boids));
        }
    }

    void update()
    {
        ctx.update = [&]() {
            ctx.background(p6::NamedColor::Blue);
            const glm::mat4 globalMVMatrix = camera.getViewMatrix();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glEnable(GL_DEPTH_TEST);

            glm::mat4 mvMatrix =
                glm::rotate(globalMVMatrix, ctx.time(), {0.f, 5.f, 0.f});

            rBoundaryCube.setMVMatrix(mvMatrix);
            rBoundaryCube.draw(camera);

            rPlayer.setMVMatrix(mvMatrix);
            rPlayer.draw(camera);

            for (auto& flock : flocks)
                flock.move();
            renderFlock(globalMVMatrix, camera);
        };
    }

    void controls()
    {
        ctx.mouse_scrolled = [&](p6::MouseScroll mouseScroll) {
            camera.moveFront(mouseScroll.dy);
        };
        ctx.mouse_dragged = [&](p6::MouseDrag mouseMove) {
            camera.rotateUp(mouseMove.position.x);
            camera.rotateLeft(mouseMove.position.y);
        };
    }

    void renderFlock(const glm::mat4 globalMVMatrix, TrackballCamera camera)
    {
        for (auto& flock : flocks)
        {
            for (auto& b : flock.getBoids()) // access by reference to avoid copying
            {
                glm::mat4 mvMatrix =
                    glm::translate(globalMVMatrix, {b.getPos() * glm::vec3{3.f}});
                mvMatrix = glm::scale(mvMatrix, glm::vec3{0.1f});

                rBoids.setMVMatrix(mvMatrix);
                rBoids.draw(camera);
            }
        }
    }

    void start()
    {
        ctx.start();
    }
};