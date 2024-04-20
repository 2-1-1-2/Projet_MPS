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

public:
    Controls(p6::Context* ctx, TrackballCamera* camera);

    void handleCameraZoom();
    void handleCameraRotation();
};