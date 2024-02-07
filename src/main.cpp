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

    Flock f(30);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        for (auto& b : f.getBoids()) // access by reference to avoid copying
        {
            ctx.circle(
                p6::Center{b.getPos()},
                p6::Radius{0.025f}
            );
        }
        f.move();
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}