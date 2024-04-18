#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Scene.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    std::srand(time(NULL));
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    Scene scene(30, 3);
    scene.update();
    scene.controls();
    scene.start();
}