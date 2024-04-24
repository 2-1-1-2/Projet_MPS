#include "Player.hpp"

Player::Player(p6::Context* ctx, TrackballCamera* camera, float* mapSize)
    : _ctx(ctx), _camera(), _controls(ctx, camera, mapSize), _position(0.f, 0.f, 0.f)
{
    if (Math::randBernouilli(0.3))
    {
        _object3D = Object3D("Amongus", "3D.vs.glsl", "tex3D.fs.glsl");
    }
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
    if (ImGui::CollapsingHeader("Player"))
    {
        ImGui::Indent();
        _controls.initializeGUI();
        if (ImGui::CollapsingHeader("Animation"))
        {
            ImGui::Indent();
            GUIhelp("Adjust the up & down character animation.");
            ImGui::SliderFloat("Animation amplitude", &_hoverAmplitude, .01f, .4f);
            ImGui::SliderFloat("Animation frequency", &_hoverFrequency, .01f, 20.f);
            ImGui::Unindent();
        }
        ImGui::Unindent();
        // ImGui::SliderFloat("Transparency", &_transparency, .0f, 1.f);
    }
}