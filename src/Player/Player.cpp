#include "Player.hpp"

Player::Player(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(), _controls(ctx, camera), _position(0.f, 0.f, 0.f)
{
}

void Player::handleControls()
{
    _controls.handleCameraZoom();
    _controls.handleCameraRotation();
}

void Player::handleMovements()
{
    _controls.handlePlayerMovements(_position);
}