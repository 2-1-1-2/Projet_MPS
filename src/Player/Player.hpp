#pragma once
#include <vector>
#include "Cameras/TrackballCamera.hpp"
#include "Controls.hpp"
#include "Primitives/Object3D.hpp"
#include "Shapes/Common.hpp"
#include "p6/p6.h"

class Player {
private:
    p6::Context*     _ctx;
    TrackballCamera* _camera;
    Controls         _controls;
    glm::vec3        _position{0.f, 0.f, 0.f};

    Object3D _object3D{"Ghost", "3D.vs.glsl", "tex3D.fs.glsl"};

    float _hoverAmplitude = 0.1f; // [GUI]
    float _hoverFrequency = 2.0f; // [GUI]
    float _hoverTime      = 0.0f;

    float _transparency = 1.f; // [GUI]

public:
    Player(p6::Context* ctx, TrackballCamera* camera, float* mapSize);

    void handleControls();
    void handleMovements();
    void animatePlayer();
    void initializeGUI();

    Object3D&  getObject3D() { return _object3D; };
    glm::vec3& getPosition() { return _position; };
    float      getLastOrientation() { return glm::degrees(atan2(_controls.getLastDirection().z, _controls.getLastDirection().x)) + 90.0f; };
    float      getTransparency() const { return _transparency; };
    void       setPosition(const glm::vec3& position) { _position = position; };
};