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

public:
    Player(p6::Context* ctx, TrackballCamera* camera);

    void handleControls();
};