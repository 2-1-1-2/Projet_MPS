#include "Player.hpp"

Player::Player(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(), _controls(ctx, camera)
{
}

void Player::handleControls()
{
    _controls.handleCameraZoom();
    _controls.handleCameraRotation();
}