#pragma once
#include <cmath>
#include <cstddef>
#include <vector>
#include "Boids/Flock.hpp"
#include "Cameras/TrackballCamera.hpp"
#include "GUI/GUIhelper.hpp"
#include "Maths/Math.hpp"
#include "Player/Player.hpp"
#include "Primitives/Model.hpp"
#include "Primitives/Object3D.hpp"
#include "Primitives/Transform.hpp"
#include "Renderer/GlobalRenderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

struct Scene {
    float    cubeBaseSize             = 10.f; // for reference only, do not touch
    float    groundBaseSize           = 2.f;  // for reference only, do not touch
    float    size                     = 50.f; // [GUI]
    float    groundLevel              = 5.f;  // [GUI]
    float    boundingCubeTransparency = 1.f;
    Object3D boundingCube{"BoundingCube", "skybox.vs.glsl", "skybox.fs.glsl"};
    Object3D ground{"Ground", "base3D.vs.glsl", "base3D.fs.glsl"};

    std::vector<std::pair<float, float>> positions;
    std::vector<Object3D>                grave = {};
    std::vector<Object3D>                hand  = {};
};

class App {
private:
    // Game logic
    p6::Context     _ctx = p6::Context{{.title = "Ghost & Graves"}};
    GlobalRenderer  _renderer{&_ctx, &_camera};
    TrackballCamera _camera{&_player.getPosition()};

    // Game elements
    Player             _player{&_ctx, &_camera, &_scene.size};
    std::vector<Flock> _flocks;
    Scene              _scene;

    int              _LoD = 3;         // [GUI]
    BoidsMultipliers boidsMultipliers; // [GUI]

    int _nb_boids  = 100; // [GUI]
    int _nb_flocks = 5;   // [GUI]

    void regulateFlocks()
    {
        while (_flocks.size() > static_cast<size_t>(_nb_flocks))
        {
            _flocks.pop_back();
        }
        while (_flocks.size() < static_cast<size_t>(_nb_flocks))
        {
            _flocks.emplace_back(_nb_boids);
        }
    }

    void regulateBoids()
    {
        for (auto& flock : _flocks)
        {
            flock.regulateBoids(_nb_boids);
        }
    }
    void limitsBoids()
    {
        for (auto& flock : _flocks)
        {
            flock.setLimits(_scene.size / _scene.groundBaseSize);
        }
    }

    void gameLogic()
    {
        for (auto& flock : _flocks)
        {
            limitsBoids();
            flock.move(boidsMultipliers);
        }

        _player.handleMovements();
    }

    void render()
    {
        _renderer.clearAll();

        _ctx.background(p6::NamedColor::Blue);

        Transform groundTransform{{0.f, -1.f, 0.f}, {0.f, 0.f, 0.f}, _scene.size / _scene.groundBaseSize};
        _renderer.drawObject(groundTransform.getTransform(), _scene.ground);

        for (unsigned int i = 0; i < _scene.grave.size(); i++)
        {
            Transform graveTransform{{_scene.positions[i].first, -1.f, _scene.positions[i].second}, {0.f, 0.f, 0.f}, .7f};
            _renderer.drawObject(graveTransform.getTransform(), _scene.grave[i]);
        }

        float hand_position = (static_cast<int>(_ctx.time()) / 2 % 2 == 0 ? -std::fmod(_ctx.time(), 2.f) : std::fmod(_ctx.time(), 2.f) - 2.f) - 1.2f;
        for (unsigned int i = 0; i < _scene.hand.size(); i++)
        {
            Transform graveTransform{{_scene.positions[i].first, -1.f, _scene.positions[i].second}, {0.f, 0.f, 0.f}, .7f};
            _renderer.drawObject(graveTransform.getTransform(), _scene.grave[i]);

            Transform handTransform{{_scene.positions[i].first + 1.2f, (hand_position), _scene.positions[i].second}, {0.f, 90.f, 0.f}, .2f};
            _renderer.drawObject(handTransform.getTransform(), _scene.hand[i]);
        };

        renderFlock();

        _player.animatePlayer();
        Transform ghostTransform{_player.getPosition(), {0.f, -_player.getLastOrientation() + 180, 0.f}, .3f};
        _renderer.drawObject(ghostTransform.getTransform(), _player.getObject3D(), _player.getTransparency());

        Transform boundingCubeTransform{{0.f, (_scene.size / 2) - _scene.groundLevel, 0.f}, {0.f, 0.f, 0.f}, _scene.size / _scene.cubeBaseSize};
        _renderer.drawObject(boundingCubeTransform.getTransform(), _scene.boundingCube, _scene.boundingCubeTransparency);

        regulateFlocks();
        regulateBoids();
    }

    void renderFlock()
    {
        for (auto& flock : _flocks)
        {
            for (auto& boids : flock.getBoids()) // access by reference to avoid copying
            {
                Transform flockTransform{boids.getPos() * glm::vec3{3.f}, {0.f, 0.f, 0.f}, .075f};
                _renderer.drawObject(flockTransform.getTransform(), flock.getObject3D(_LoD));
            }
        }
    }

    void cleanUp()
    {
        _scene.boundingCube.clear();
        _scene.ground.clear();
        _scene.grave.clear();
        _scene.hand.clear();
        _player.getObject3D().clear();
    }

public:
    explicit App()
    {
        _ctx.maximize_window();

        // Instantiate flock
        for (size_t i = 0; i < static_cast<size_t>(_nb_flocks); i++)
        {
            _flocks.push_back(Flock(_nb_boids));
        }

        size_t nb = Math::randBinomial(0.6, 15);
        for (size_t i = 0; i < nb; i++)
        {
            _scene.positions.push_back(std::make_pair(Math::randBeta(0.5, 0.5, -10, 10), Math::randBeta(0.5, 0.5, -10, 10)));

            _scene.grave.push_back(Object3D("Grave", "base3D.vs.glsl", "base3D.fs.glsl"));

            _scene.hand.push_back(Object3D("Hand", "base3D.vs.glsl", "base3D.fs.glsl"));
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
            initializeGUI();
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

private:
    void initializeGUI()
    {
        ImGui::Begin("Parameters");

        if (ImGui::CollapsingHeader("Scene"))
        {
            ImGui::Indent();
            ImGui::SliderFloat("Bounding box size", &_scene.size, 7.f, 200.f);
            GUIhelp("Size of the cube bounding the player and the boids.");
            ImGui::SliderFloat("Bounding box transparency", &_scene.boundingCubeTransparency, 0.f, 1.f);
            ImGui::SliderFloat("Ground level", &_scene.groundLevel, 1.f, _scene.size - 1.f);
            GUIhelp("Change the ground level of the scene inside the cube.");
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Boids"))
        {
            ImGui::Indent();
            ImGui::SliderInt("Nb of boids", &_nb_boids, 0, 100);
            ImGui::SliderInt("Nb of flocks", &_nb_flocks, 0, 10);
            ImGui::SliderInt("LoD", &_LoD, 1, 3);
            GUIhelp("Change quality of the boid's model. The higher the better.");
            ImGui::SliderFloat("Speed", &boidsMultipliers.speed, 0.f, 20.f);
            ImGui::SliderFloat("Avoid", &boidsMultipliers.avoid, 0.f, 5.f);
            ImGui::SliderFloat("Alignment", &boidsMultipliers.alignment, 0.f, 5.f);
            ImGui::SliderFloat("Cohesion", &boidsMultipliers.cohesion, 0.f, 5.f);
            ImGui::Unindent();
        }

        _player.initializeGUI();
        _renderer.initializeGUI();

        ImGui::End();
    }
};