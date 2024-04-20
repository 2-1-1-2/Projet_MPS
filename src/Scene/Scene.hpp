#pragma once
#include <vector>
#include "Boids/Flock.hpp"
#include "Cameras/TrackballCamera.hpp"
#include "Player/Player.hpp"
#include "Primitives/Model.hpp"
#include "Primitives/Object3D.hpp"
#include "Primitives/Transform.hpp"
#include "Renderer/GlobalRenderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Scene {
    /*
    - Taille de la scene
    - Position de la scene
    */

private:
    int _sceneSize = 10.f;

    p6::Context _ctx = p6::Context{{.title = "Projet_MPS"}}; // plutôt à mettre dans le main et à passer en parametre ?

    std::vector<Flock> _flocks;
    TrackballCamera    _camera;
    GlobalRenderer     _renderer;
    Player             _player;

    // Create the 3D objects, load the .obj files, textures and shaders
    Object3D boundingCube{"BoundingCube", "3D.vs.glsl", "tex3D.fs.glsl"};
    Object3D ghost{"Ghost", "3D.vs.glsl", "tex3D.fs.glsl"};

public:
    explicit Scene(unsigned int nb_boids, unsigned int nb_flocks)
        : _renderer(&_ctx, &_camera), _player(&_ctx, &_camera)
    {
        _ctx.maximize_window();

        // Instantiate flock
        for (unsigned int i = 0; i < nb_flocks; i++)
        {
            _flocks.push_back(Flock(nb_boids));
        }

        _player.handleControls();
    }

    void update()
    {
        _ctx.update = [&]() {
            _ctx.background(p6::NamedColor::Blue);
            const glm::mat4 globalMVMatrix = _camera.getViewMatrix();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glEnable(GL_DEPTH_TEST);

            // glm::mat4 mvMatrix =
            //     glm::rotate(globalMVMatrix, ctx.time(), {0.f, 5.f, 0.f});

            Transform boundingCubeTransform{{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, 10.f};
            _renderer.drawObject(boundingCubeTransform.getTransform(), boundingCube);
            Transform ghostTransform{{0.f, 0.f, 0.f}, {0.f, 45.f, 45.f}, .3f};
            _renderer.drawObject(ghostTransform.getTransform(), ghost);

            for (auto& flock : _flocks)
                flock.move();
            renderFlock(globalMVMatrix);
        };

        _renderer.close();
    }

    void renderFlock(const glm::mat4 globalMVMatrix)
    {
        for (auto& flock : _flocks)
        {
            for (auto& b : flock.getBoids()) // access by reference to avoid copying
            {
                // glm::mat4 mvMatrix =
                //     glm::translate(globalMVMatrix, {});
                // mvMatrix = glm::scale(mvMatrix, glm::vec3{0.1f});

                Transform flockTransform{b.getPos() * glm::vec3{3.f}, {0.f, 0.f, 0.f}, .05f};
                _renderer.drawObject(flockTransform.getTransform(), ghost);
                // rBoids.setMVMatrix(mvMatrix);
                // rBoids.draw(_camera);
            }
        }
    }

    void start()
    {
        _ctx.start();
    }
};