#include "Controls.hpp"

Controls::Controls(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(camera){};

void Controls::handleCameraZoom()
{
    _ctx->mouse_scrolled = [&](p6::MouseScroll scroll) {
        if (scroll.dy > 0 && (_camera->getDistance() - _scrollSensitivity >= _minSrcollDistance))
        {
            _camera->moveFront(_scrollSensitivity);
        }
        else if (scroll.dy < 0 && (_camera->getDistance() + _scrollSensitivity <= _maxScrollDistance))
        {
            _camera->moveFront(-_scrollSensitivity);
        }
    };
};

void Controls::handleCameraRotation()
{
    _ctx->mouse_dragged = [&](p6::MouseDrag mouse_drag) {
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
            return;
        _camera->rotateLeft(-mouse_drag.delta.x * _mouseSensitivity);
        _camera->rotateUp(mouse_drag.delta.y * _mouseSensitivity);
    };
}

void Controls::handlePlayerMovements(glm::vec3& playerPosition)
{
    glm::vec3 forward = glm::vec3(
        sin(glm::radians(_camera->getAngleY())), // Horizontal angle in radians
        0,                                       // No vertical movement in Y-axis
        -cos(glm::radians(_camera->getAngleY())) // Horizontal angle in radians
    );

    glm::vec3 right = glm::vec3(
        cos(glm::radians(_camera->getAngleY())), // Perpendicular to forward vector
        0,
        sin(glm::radians(_camera->getAngleY()))
    );

    if (_ctx->key_is_pressed(GLFW_KEY_W))
    {
        playerPosition += forward * _movementSpeed; // Move forward
    }
    if (_ctx->key_is_pressed(GLFW_KEY_S))
    {
        playerPosition -= forward * _movementSpeed; // Move backward
    }
    if (_ctx->key_is_pressed(GLFW_KEY_A))
    {
        playerPosition -= right * _movementSpeed; // Move left
    }
    if (_ctx->key_is_pressed(GLFW_KEY_D))
    {
        playerPosition += right * _movementSpeed; // Move right
    }
    // _camera->setTarget(playerPosition); // Update camera to follow the player
}