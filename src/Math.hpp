#pragma once
#include <cmath>
#include <cstdlib>
class Math {
private:
public:
    // TODO(tanya): voir pour faire un intervalle
    static float randomFloat()
    {
        constexpr int N   = 10000;
        float         res = 0;
        for (int i = 1; i < N; i++)
        {
            res += static_cast<float>(rand() % 2) / static_cast<float>(pow(2, i));
        }

        return res;
    }

    static int randomSign()
    {
        return (rand() % 2) == 0 ? 1 : -1;
    }
};