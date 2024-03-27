#include <vector>
#include "./3D/Renderer.hpp"
#include "./Boids/Flock.hpp"
#include "3D/common/TrackballCamera.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Scene {
    /*
    - Taille de la scene
    - Position de la scene

    */

private:
    p6::Context        ctx = p6::Context{{.title = "Projet_MPS"}};
    std::vector<Flock> flocks;
    Renderer           world  = Renderer(&ctx, new LightProgram("../src/3D/shaders/3D.vs.glsl", "../src/3D/shaders/pointLight.fs.glsl"));
    Renderer           rBoids = Renderer(&ctx, new LightProgram("../src/3D/shaders/3D.vs.glsl", "../src/3D/shaders/pointLight.fs.glsl"));
    TrackballCamera    camera;

public:
    explicit Scene(int nb)

    {
        ctx.maximize_window();
        world.setup();
        rBoids.setup();

        // TODO: Faire un cube
        std::vector<glimac::ShapeVertex> vertices = glimac::sphere_vertices(1.f, 32, 16);

        world.setVertices(vertices);

        for (unsigned int i = 0; i < 2; i++)
        {
            flocks.push_back(Flock(nb));
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

            world.setMVMatrix(mvMatrix);
            world.draw(camera);

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

    void start() { ctx.start(); }
};