#pragma once
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

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
        return static_cast<int>(randomFloat(min, max));
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
        return randomFloat() <= proba;
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

    static float randExponential(float lambda) { return -std::log(1 - randomFloat()) / lambda; }

    static float randNormale()
    {
        float u1 = randomFloat();
        float u2 = randomFloat();

        return std::sqrt(-2.0f * std::log(u1)) * std::cos(2.0f * static_cast<float>(M_PI) * u2);
    }

    static float randBeta()
    {
        return 0;
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
};