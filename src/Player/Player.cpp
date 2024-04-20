#include "Player.hpp"

Player::Player(p6::Context* ctx, TrackballCamera* camera, float* mapSize)
    : _ctx(ctx), _camera(), _controls(ctx, camera, mapSize), _position(0.f, 0.f, 0.f)
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

void Player::animatePlayer()
{
    _hoverTime += _ctx->delta_time();
    float hoverDelta = _hoverAmplitude * sin(_hoverFrequency * _hoverTime);
    _position.y      = 0 + hoverDelta;
}