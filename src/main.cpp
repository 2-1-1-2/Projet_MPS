#include <cstdlib>
#include "Flock.hpp"
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    std::srand(time(0));
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Projet_MPS"}};
    ctx.maximize_window();

    Flock f(10);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
        ctx.circle(
            p6::Center{glm::vec2(1, 1)},
            p6::Radius{0.05f}
        );
        ctx.circle(
            p6::Center{glm::vec2(0, 0)},
            p6::Radius{0.05f}
        );
        ctx.circle(
            p6::Center{glm::vec2(1.5, 1)},
            p6::Radius{0.05f}
        );

        std::vector<Boid>
            t = f.getBoids();
        for (auto& b : t) // access by reference to avoid copying
        {
            ctx.circle(
                p6::Center{b.getPos()},
                p6::Radius{0.05f}
            );
        }
        f.move();
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}