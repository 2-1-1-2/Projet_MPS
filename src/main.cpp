#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "App/App.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    App App;

    // Setup context GUI and update loop
    App.GUI();
    App.update();

    App.start();
    App.stop();
}