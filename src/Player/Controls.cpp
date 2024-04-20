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