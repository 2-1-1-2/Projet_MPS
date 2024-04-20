#include "Controls.hpp"

Controls::Controls(p6::Context* ctx, TrackballCamera* camera)
    : _ctx(ctx), _camera(camera){};

void Controls::handleCameraZoom()
{
    _ctx->mouse_scrolled = [&](p6::MouseScroll scroll) {
        if (scroll.dy > 0)
        {
            _camera->moveFront(4.8f);
        }
        else if (scroll.dy < 0)
        {
            _camera->moveFront(-4.8f);
        }
        std::cout << "salut c moi je scroll" << std::endl;
    };
};

void Controls::handleCameraRotation()
{
    std::cout << "allo la police" << std::endl;
    _ctx->mouse_dragged = [&](p6::MouseDrag mouse_drag) {
        if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
            return;
        std::cout << "oui c moi je rotate" << std::endl;
        _camera->rotateLeft(-mouse_drag.delta.x * 90.f);
        _camera->rotateUp(mouse_drag.delta.y * 90.f);
    };
}