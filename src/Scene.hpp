#include "Flock.hpp"
#include "p6/p6.h"
class Scene {
    /*
    - Taille de la scene
    - Position de la scene

    */

private:
    p6::Context ctx = p6::Context{{.title = "Projet_MPS"}};
    Flock       flocks;

public:
    explicit Scene(int nb)
        : flocks(nb)
    {
        ctx.maximize_window();
    }

    void update()
    {
        ctx.update = [&]() {
            ctx.background(p6::NamedColor::Blue);
            renderFlock();
            flocks.move();
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