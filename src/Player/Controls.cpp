#include "Controls.hpp"

Controls::Controls(p6::Context* ctx, TrackballCamera* camera, float* mapSize)
    : _ctx(ctx), _camera(camera), _mapSize(mapSize){};

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
    glm::vec3 newDirection = glm::vec3(0);

    if (_ctx->key_is_pressed(GLFW_KEY_W))
    {
        newDirection += glm::vec3(sin(glm::radians(_camera->getAngleY())), 0, -cos(glm::radians(_camera->getAngleY())));
    }
    if (_ctx->key_is_pressed(GLFW_KEY_S))
    {
        newDirection -= glm::vec3(sin(glm::radians(_camera->getAngleY())), 0, -cos(glm::radians(_camera->getAngleY())));
    }
    if (_ctx->key_is_pressed(GLFW_KEY_A))
    {
        newDirection -= glm::vec3(cos(glm::radians(_camera->getAngleY())), 0, sin(glm::radians(_camera->getAngleY())));
    }
    if (_ctx->key_is_pressed(GLFW_KEY_D))
    {
        newDirection += glm::vec3(cos(glm::radians(_camera->getAngleY())), 0, sin(glm::radians(_camera->getAngleY())));
    }

    if (glm::length(newDirection) > 0)
    { // Only update if there has been movement
        _lastDirection                 = glm::normalize(newDirection);
        glm::vec3   newPosition        = playerPosition + _lastDirection * _movementSpeed;
        const float halfSizeWithMargin = ((*_mapSize / 2) - _margin);
        newPosition.x                  = std::clamp(newPosition.x, -halfSizeWithMargin, halfSizeWithMargin);
        newPosition.z                  = std::clamp(newPosition.z, -halfSizeWithMargin, halfSizeWithMargin);
        playerPosition                 = newPosition;
    }
}