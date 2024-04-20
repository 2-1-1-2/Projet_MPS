#pragma once
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

public:
    Controls(p6::Context* ctx, TrackballCamera* camera);

    void handleCameraZoom();
    void handleCameraRotation();
};