#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include "Cameras/TrackballCamera.hpp"
#include "Primitives/Object3D.hpp"
#include "Shapes/Common.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/matrix.hpp"
#include "p6/p6.h"


class Controls {
private:
    p6::Context*     _ctx;
    TrackballCamera* _camera;

    /// TODO: à mettre dans le GUI
    float _scrollSensitivity = .2f;
    float _mouseSensitivity  = 90.f;

    /// TODO: à mettre dans le GUI
    float _minSrcollDistance = .5f;
    float _maxScrollDistance = 5.f;

    // TODO: à mettre dans le GUI
    float _movementSpeed = .1f;

public:
    Controls(p6::Context* ctx, TrackballCamera* camera);

    void handleCameraZoom();
    void handleCameraRotation();
    void handlePlayerMovements(glm::vec3& playerPosition);
};