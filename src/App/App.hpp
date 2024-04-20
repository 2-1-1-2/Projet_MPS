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

struct Scene {
    const float cubeBaseSize = 10.f;
    float       size         = 100.f;
    float       groundLevel  = 5.f;
    Object3D    boundingCube{"BoundingCube", "3D.vs.glsl", "tex3D.fs.glsl"};
    Object3D    environment{"BoundingCube", "3D.vs.glsl", "tex3D.fs.glsl"};
};

class App {
private:
    // Game logic
    p6::Context     _ctx = p6::Context{{.title = "Projet_MPS"}}; // plutôt à mettre dans le main et à passer en parametre ?
    GlobalRenderer  _renderer;
    TrackballCamera _camera;

    // Game elements
    Player             _player;
    std::vector<Flock> _flocks;
    Scene              _scene;

    void gameLogic()
    {
        for (auto& flock : _flocks)
            flock.move();

        _player.handleMovements();
    }

    void render()
    {
        _renderer.clearAll();

        _ctx.background(p6::NamedColor::Blue);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        Transform boundingCubeTransform{{0.f, (_scene.size / 2) - _scene.groundLevel, 0.f}, {0.f, 0.f, 0.f}, _scene.size / _scene.cubeBaseSize};
        _renderer.drawObject(boundingCubeTransform.getTransform(), _scene.boundingCube);

        Transform ghostTransform{_player.getPosition(), {0.f, -_player.getLastOrientation() + 180, 0.f}, .3f};
        _renderer.drawObject(ghostTransform.getTransform(), _player.getObject3D());

        renderFlock();
    }

    void renderFlock()
    {
        for (auto& flock : _flocks)
        {
            for (auto& b : flock.getBoids()) // access by reference to avoid copying
            {
                Transform flockTransform{b.getPos() * glm::vec3{3.f}, {0.f, 0.f, 0.f}, .05f};
                _renderer.drawObject(flockTransform.getTransform(), _player.getObject3D());
            }
        }
    }

    void cleanUp()
    {
        _scene.boundingCube.clear();
        _player.getObject3D().clear();
    }

public:
    explicit App(unsigned int nb_boids, unsigned int nb_flocks)
        : _renderer(&_ctx, &_camera), _player(&_ctx, &_camera), _camera(&_player.getPosition())
    {
        _ctx.maximize_window();

        // Instantiate flock
        for (unsigned int i = 0; i < nb_flocks; i++)
        {
            _flocks.push_back(Flock(nb_boids));
        }

        _player.handleControls();
    }

    ~App()
    {
        cleanUp();
    }

    void update()
    {
        _ctx.update = [&]() {
            gameLogic();
            render();
        };
    }

    void start()
    {
        _ctx.start();
    }

    void stop()
    {
        cleanUp();
    }
};