#pragma once
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

class Math {
private:
public:
    static float rand()
    {
        thread_local std::default_random_engine gen{std::random_device{}()};
        thread_local auto                       distrib = std::uniform_real_distribution<float>{0.0, 1.0};

        return distrib(gen);
    }

    static int randUniformD(int min = 0, int max = 1)
    {
        return static_cast<int>(round(rangeProba(rand(), static_cast<float>(min), static_cast<float>(max))));
    }

    static float randUniformC(float min = 0, float max = 1)
    {
        return rangeProba(rand(), min, max);
    }

    static bool randBernouilli(float proba)
    {
        return rand() <= proba;
    }

    static int randBinomial(float proba, float n)
    {
        int success = 0;
        for (unsigned int i = 0; i < static_cast<unsigned int>(n); i++)
        {
            if (randBernouilli(proba))
            {
                success += 1;
            }
        }
        return success;
    }

    static float randExponential(float lambda)
    {
        return -std::log(1 - randUniformC()) / lambda;
    }

    static float randNormale()
    {
        float _u1 = noZeroRand();
        float _u2 = randUniformC();

        return std::sqrt(-2.0f * std::log(_u1)) * std::cos(2.0f * static_cast<float>(M_PI) * _u2);
    }

    static float randBeta(float alpha, float beta, float min = 0, float max = 1)

    {
        float _u1 = rand();
        float _u2 = rand();
        while (pow(_u1, 1. / alpha) + pow(_u2, 1. / beta) > 1)
        {
            _u1 = rand();
            _u2 = rand();
        }
        const float v_y = pow(_u1, 1.f / alpha) / ((pow(_u1, 1.f / alpha) + pow(_u2, 1.f / beta)));

        std::cout << "beta dist : " << v_y << "\n";

        return rangeProba(v_y, min, max);
    }
    static float noZeroRand() // Pour éviter les 0 dans les log
    {
        float v_x = randUniformC();
        while (v_x == 0)
        {
            v_x = randUniformC();
        }
        return v_x;
    }

    static float randHyperGeom()
    {
        return 0;
    }

    static float rangeProba(float proba, float min, float max)
    {
        if (min > max)
        {
            std::swap(min, max);
        }
        return min + proba * (max - min);
    }

    static int markovChain(int state)
    {
        const std::vector<std::vector<float>> stateMarkovProb = {{0.4, 0.4, 0.2}, {0.2, 0.4, 0.4}, {0.1, 0.1, 0.8}};

        const float rand = randUniformC();
        int         cpt  = 0;
        float       acc  = stateMarkovProb[state][cpt];
        while (cpt < 3 && rand > acc)
        {
            cpt++;
            acc += stateMarkovProb[state][cpt];
        }

        return cpt;
    }

    static float esperance(const std::vector<float>& draws)
    {
        float sum = 0.0;
        for (float val : draws)
        {
            sum += val;
        }
        return sum / static_cast<float>(draws.size());
    }

    static float variance(const std::vector<float>& draws)
    {
        float moyenne       = esperance(draws);
        float sumSquareDiff = 0.0;
        for (float val : draws)
        {
            float diff = val - moyenne;
            sumSquareDiff += diff * diff;
        }
        return sumSquareDiff / static_cast<float>(draws.size());
    }
};