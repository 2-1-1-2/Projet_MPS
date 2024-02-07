#pragma once
#include <cassert>
#include <vector>
#include "Boid.hpp"

class Flock {
private:
    std::vector<Boid> boids;

public:
    explicit Flock(const unsigned int number)
        : boids(number) {}

    std::vector<Boid> getBoids() const { return boids; }

    void move()
    {
        for (auto& b : boids)
        {
            b.move(boids);
        }
    }

private:
    void addBoid() { boids.emplace_back(Boid()); }
    void deleteBoid() { boids.pop_back(); }

    void populateFlock(const unsigned int number)
    {
        assert(number > 0);
        for (unsigned int i = 0; i < number; i++)
        {
            addBoid();
        }
    }

    void deleteBoids(const unsigned int number)
    {
        assert(number > 0);
        for (unsigned int i = 0; i < number; i++)
        {
            deleteBoid();
        }
    }
};