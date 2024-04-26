#pragma once
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include "Math.hpp"

class MathTest {
private:
public:
    static void randUniformDTest()
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(static_cast<float>(Math::randUniformD()));
        }
        testProb(draws, "uniforme discrète");
        std::cout << "E(X) = " << 1 / 2. << "\n";
        std::cout << "V(X) = " << ((1 * 1) - 1) / 12 << "\n\n";
    }

    static void randUniformCTest()
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(Math::randUniformC());
        }
        testProb(draws, "uniforme continue");

        std::cout << "E(X) = " << 1 / 2. << "\n";
        std::cout << "V(X) = " << 1 / 12 << "\n\n";
    }

    static void randBernouilliTest(float proba)
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(Math::randBernouilli(proba));
        }
        testProb(draws, "bernouilli");

        std::cout << "E(X) = " << proba << "\n";
        std::cout << "V(X) = " << proba * (1 - proba) << "\n\n";
    }

    static void randBinomialTest(float proba, int n)
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(static_cast<float>(Math::randBinomial(proba, n)));
        }
        testProb(draws, "binomial");

        std::cout << "E(X) = " << proba * n << "\n";
        std::cout << "V(X) = " << proba * n * (1 - proba) << "\n\n";
    }

    static void randExponentialTest(float lambda)
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(Math::randExponential(lambda));
        }
        testProb(draws, "exponential");
        std::cout << "E(X) = " << 1. / lambda << "\n";
        std::cout << "V(X) = " << 1. / (lambda * lambda) << "\n\n";
    }

    static void randNormaleTest()
    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(Math::randNormale());
        }
        testProb(draws, "normale");

        std::cout << "E(X) = 0\n";
        std::cout << "V(X) = 1\n\n";
    }

    static void randBetaTest(float alpha, float beta)

    {
        std::vector<float> draws;
        for (unsigned int i = 0; i < 2000; i++)
        {
            draws.emplace_back(Math::randBeta(alpha, beta));
        }
        testProb(draws, "normale");
    }

    /*     static void randHyperGeomTest(float proba, int N)
        {
            std::vector<float> draws;
            for (unsigned int i = 0; i < 2000; i++)
            {
                draws.emplace_back(Math::randHyperGeom(proba, N));
            }
            testProb(draws, "hyper geom");

            std::cout << "E(X) = (_n * _m) / N\n";
            std::cout << "V(X) = ((N - _n)/(N - 1)) *((_n * _m) / N)*(1-(m/n))\n\n";
        } */

    static void testProb(const std::vector<float>& draws, const std::string& probName = "")
    {
        std::cout << "Loi prob : " << probName << "\n";
        std::cout << "esperance : " << Math::esperance(draws) << "\n";
        std::cout << "variance : " << Math::variance(draws) << "\n\n";
    }
};