#include "./3D/Renderer.hpp"
#include "./boids/Flock.hpp"
#include "p6/p6.h"

class Scene {
    /*
    - Taille de la scene
    - Position de la scene

    */

private:
    p6::Context ctx = p6::Context{{.title = "Projet_MPS"}};
    Flock       flocks;
    Renderer    renderer = Renderer(&ctx);

public:
    explicit Scene(int nb)
        : flocks(nb)
    {
        ctx.maximize_window();
        renderer.setup();
    }

    void update()
    {
        ctx.update = [&]() {
            ctx.background(p6::NamedColor::Blue);
            renderFlock();
            flocks.move();
            renderer.draw();
        };
    }

    void controls()
    {
        ctx.mouse_scrolled = [&](p6::MouseScroll mouseScroll) {
            renderer.camera.moveFront(mouseScroll.dy);
        };
        ctx.mouse_dragged = [&](p6::MouseDrag mouseMove) {
            renderer.camera.rotateUp(mouseMove.position.x);
            renderer.camera.rotateLeft(mouseMove.position.y);
        };
    }

    void renderFlock()
    {
        for (auto& b : flocks.getBoids()) // access by reference to avoid copying
        {
            ctx.circle(
                p6::Center{b.getPos()},
                p6::Radius{0.025f}
            );
        }
    }

    void start() { ctx.start(); }
};