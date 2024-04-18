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

public:
    explicit Scene(int nb_boids, int nb_flocks)

    {
        ctx.maximize_window();
        rBoundaryCube.setup();
        rPlayer.setup();
        rBoids.setup();

        /// TODO: Faire un cube
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
        ctx.mouse_moved = [&](p6::MouseMove mouseMove) {
            /// TODO: ajouter la sensi au GUI
            const float sensitivity = 150.f;
            camera.rotateLeft(mouseMove.delta.x * sensitivity);
            camera.rotateUp(-mouseMove.delta.y * sensitivity); // invert Y for a more intuitive rotation
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll mouseScroll) {
            camera.moveFront(mouseScroll.dy);
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