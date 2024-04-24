#pragma once
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

class Math {
private:
public:
    // TODO(tanya): voir pour faire un intervalle
    /*     static float randomFloat()
        {
            constexpr int N   = 10000;
            float         res = 0;
            for (int i = 1; i < N; i++)
            {
                res += static_cast<float>(rand() % 2) / static_cast<float>(pow(2, i));
            }

            return res;
        } */

    static float rand()
    {
        static std::random_device                    rand;
        static std::mt19937                          gen(rand());
        static std::uniform_real_distribution<float> dis(0.0, 1.0);

        return dis(gen);
    }
    static float randomFloat(float min = 0, float max = 1)
    {
        if (min > max)
        {
            std::swap(min, max);
        }
        return min + rand() * (max - min);
    }

    static int randomInt(int min = 0, int max = 1)
    {
        return round(randomFloat(min, max));
    }

    static int randomSign()
    {
        return (randomInt() % 2) == 0 ? 1 : -1;
    }

    static float randUniformD(int min, int max)
    {
        return randomInt(min, max);
    }

    static float randUniformC(int min, int max)
    {
        return randomFloat(min, max);
    }

    static bool randBernouilli(float proba)
    {
        static const float x = randomFloat();
        toString("Binomial", proba, x);
        return x <= proba;
    }

    static float randBinomial(float proba, float n)
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

    static float randExponential(float lambda)
    {
        /* float proba = lambda * exp((-lambda) * t);  */ // proba de x > t
        return 1;
    }

    static float randBeta()
    {
        return 0;
    }

    static float randHyperGeom()
    {
        return 0;
    }

    static float randNormale()
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

    static void allTest()
    {
    }
};