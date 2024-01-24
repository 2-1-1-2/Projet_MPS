#pragma once
#include <cmath>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
class Math {
    /*
    - Taille de la scene
    - Position de la scene

    */
private:
public:
    // TODO(tanya): voir pour faire un intervalle
    static double randomDouble(int max)
    {
        static constexpr int N = 10000;

        double res = 0;

        for (int i = 1; i < N; i++)
        {
            res += (rand() % (max + 1)) / pow(2, i);
        }

        return res;
    }

    static double randomDouble()
    {
        return randomDouble(1);
    }

    static double randomSign()
    {
        return (rand() % 2) == 0 ? 1 : -1;
    }
};