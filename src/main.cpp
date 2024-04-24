#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "App/App.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    std::srand(time(NULL));

    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    for (unsigned int i = 0; i < 100; i++)
    {
        Math::randExponential(5);
    }
    App App;

    // Setup context GUI and update loop
    App.GUI();
    App.update();

    App.start();
    App.stop();
}