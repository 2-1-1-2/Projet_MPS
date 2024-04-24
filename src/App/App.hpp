#pragma once
#include <vector>
#include "../../lib/p6/src/Context.h"
#include "../../lib/p6/src/internal/Time/Clock_Realtime.h"
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
    float    cubeBaseSize             = 10.f;  // for reference only, do not touch
    float    groundBaseSize           = 2.f;   // for reference only, do not touch
    float    size                     = 100.f; // [GUI]
    float    groundLevel              = 5.f;   // [GUI]
    float    boundingCubeTransparency = 1.f;
    Object3D boundingCube{"BoundingCube", "3D.vs.glsl", "tex3D.fs.glsl"};
    Object3D ground{"Ground", "3D.vs.glsl", "tex3D.fs.glsl"};
    Object3D grave{"Grave", "3D.vs.glsl", "tex3D.fs.glsl"};
    Object3D hand{"Hand", "3D.vs.glsl", "tex3D.fs.glsl"};
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

    /// TODO: Faire en sorte qu'on puisse le modifier dans le GUI et que ça impacte le jeu
    int _nb_boids  = 20; // [GUI]
    int _nb_flocks = 10; // [GUI]

    void showGUI()
    {
        initializeGUI();
        _player.initializeGUI();
        _renderer.initializeGUI();
    }

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

        Transform groundTransform{{0.f, -1.f, 0.f}, {0.f, 0.f, 0.f}, _scene.size / _scene.groundBaseSize};
        _renderer.drawObject(groundTransform.getTransform(), _scene.ground);

        Transform graveTransform{{5.f, -1.f, 0.f}, {0.f, 0.f, 0.f}, .7f};
        _renderer.drawObject(graveTransform.getTransform(), _scene.grave);
        Transform handTransform{{5.f + 1.2f, -1.f, 0.f}, {0.f, 90.f, 0.f}, .2f};
        _renderer.drawObject(handTransform.getTransform(), _scene.hand);

        renderFlock();

        _player.animatePlayer();
        Transform ghostTransform{_player.getPosition(), {0.f, -_player.getLastOrientation() + 180, 0.f}, .3f};
        _renderer.drawObject(ghostTransform.getTransform(), _player.getObject3D(), _player.getTransparency());

        Transform boundingCubeTransform{{0.f, (_scene.size / 2) - _scene.groundLevel, 0.f}, {0.f, 0.f, 0.f}, _scene.size / _scene.cubeBaseSize};
        _renderer.drawObject(boundingCubeTransform.getTransform(), _scene.boundingCube, _scene.boundingCubeTransparency);
    }

    void renderFlock()
    {
        for (auto& flock : _flocks)
        {
            for (auto& b : flock.getBoids()) // access by reference to avoid copying
            {
                Transform flockTransform{b.getPos() * glm::vec3{3.f}, {0.f, 0.f, 0.f}, .075f};
                _renderer.drawObject(flockTransform.getTransform(), flock.getObject3D());
            }
        }
    }

    void cleanUp()
    {
        _scene.boundingCube.clear();
        _scene.ground.clear();
        _scene.grave.clear();
        _player.getObject3D().clear();
    }

    void initializeGUI()
    {
        ImGui::Begin("Scene parameters");
        ImGui::SliderInt("Nb of boids", &_nb_boids, 0, 30);
        ImGui::SliderInt("Nb of flocks", &_nb_flocks, 0, 10);
        ImGui::SliderFloat("Bounding box size", &_scene.size, 7.f, 200.f);
        ImGui::SliderFloat("Bounding box transparency", &_scene.boundingCubeTransparency, 0.f, 1.f);
        ImGui::SliderFloat("Ground level", &_scene.groundLevel, 1.f, _scene.size - 1.f);
        ImGui::End();
    }

public:
    explicit App()
        : _renderer(&_ctx, &_camera), _player(&_ctx, &_camera, &_scene.size), _camera(&_player.getPosition())
    {
        _ctx.maximize_window();

        // Instantiate flock
        for (unsigned int i = 0; i < _nb_flocks; i++)
        {
            _flocks.push_back(Flock(_nb_boids));
        }

        _player.handleControls();
    }

    ~App()
    {
        cleanUp();
    }

    void GUI()
    {
        _ctx.imgui = [&]() {
            showGUI();
        };
    };
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