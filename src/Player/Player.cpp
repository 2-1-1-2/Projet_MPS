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

void Player::initializeGUI()
{
    _controls.initializeGUI();
    ImGui::Begin("Character look parameters");
    // ImGui::SliderFloat("Transparency", &_transparency, .0f, 1.f);
    ImGui::SliderFloat("Animation amplitude", &_hoverAmplitude, .01f, .4f);
    ImGui::SliderFloat("Animation frequency", &_hoverFrequency, .01f, 20.f);
    ImGui::End();
}