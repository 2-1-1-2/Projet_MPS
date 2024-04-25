#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "App/App.hpp"
#include "Maths/MathTest.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    std::vector<float> draws;
    MathTest::randBernouilliTest(0.7);
    MathTest::randBinomialTest(0.7, 20);
    MathTest::randUniformDTest();
    MathTest::randUniformCTest();
    MathTest::randExponentialTest(4);
    MathTest::randNormaleTest();
    /*
    MathTest::randBetaTest(0.5, 0.5);
    MathTest::randHyperGeomTest(); */
    /* App App;

    // Setup context GUI and update loop
    App.GUI();
    App.update();

    App.start();
    App.stop(); */
}