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

    App App(20, 5);
    App.update();
    App.start();
    App.stop();
}