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
    static float
        rand()
    {
        thread_local std::default_random_engine gen{std::random_device{}()};
        thread_local auto                       distrib = std::uniform_real_distribution<float>{0.0, 1.0};

        return distrib(gen);
    }

    static float randUniformD(int min = 0, int max = 1)
    {
        return static_cast<int>(rangeProba(rand(), min, max));
    }

    static float randUniformC(float min = 0, float max = 1)
    {
        return rangeProba(rand(), min, max);
    }

    static bool randBernouilli(float proba)
    {
        return randUniformC() <= proba;
    }

    static int randBinomial(float proba, float n)
    {
        static int success;
        for (unsigned int i = 0; i < n; i++)
        {
            if (randBernouilli(proba))
            {
                success += 1;
            }
        }
        return success;
    }

    static float randExponential(float lambda) { return -std::log(1 - randUniformC()) / lambda; }

    static float randNormale()
    {
        float u1 = noZeroRand();
        float u2 = randUniformC();

        return std::sqrt(-2.0f * std::log(u1)) * std::cos(2.0f * static_cast<float>(M_PI) * u2);
    }

    static float randBeta(float alpha, float beta, float min = 0, float max = 1)
    {
        float u1     = noZeroRand();
        float u2     = noZeroRand();
        float gamma1 = -log(u1);
        float gamma2 = -log(u2);

        float random_beta = gamma1 / (gamma1 + gamma2);
        /* std::cout << "BETA :" << random_beta * (alpha + beta) / alpha << "\n"; */

        float x = 0.0;

        for (int i = 0; i < 2000; i++)
        {
            x = randUniformC();
            if (x < beta / (beta + alpha))
                beta += 1.0;
            else
                alpha += 1.0;
        }
        /* std::cout << "BETA :" << alpha / (beta + alpha) << "with range" <<  rangeProba(alpha / (beta + alpha), min, max) << "\n";*/

        return rangeProba(alpha / (beta + alpha), min, max);
    }
    static float noZeroRand() // Pour éviter les 0 dans les log
    {
        float x = randUniformC();
        while (x == 0)
        {
            x = randUniformC();
        }
        return x;
    }

    static float randHyperGeom()
    {
        return 0;
    }

    static void toString(std::string name, float proba, float tirage)
    {
        std::cout << "Loi" << name << "\nProba : " << proba << "\nTirage : " << tirage << "\n\n\n";
    }

    static float esperance()
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

    static int
        markovChain(int state)
    {
        static std::vector<std::vector<float>> stateMarkovProb = {{0.4, 0.3, 0.4}, {0.2, 0.4, 0.4}, {0.3, 0.3, 0.4}};
        // verification de la somme des proba
        /*
        float                                  sum             = std::accumulate(stateMarkovProb[state].begin(), stateMarkovProb[state].end(), 0.);
        if (sum != 1)
            return -1; */

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
};