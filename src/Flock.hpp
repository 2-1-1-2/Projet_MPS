#pragma once
#include <vector>
#include "Boid.hpp"

class Flock {
    /*
    - liste de boids
    - construction modérée de boids (1 seul boid?)
    - constructions massive de boids ?
    - destruction de boids

------- caractéristique pour une famille -----
    - Séparation
    - Alignement
    - Cohésion
    */
private:
    std::vector<Boid> boids;

public:
    explicit Flock(const unsigned int number)
    {
        for (unsigned int i = 0; i < number; i++)
            boids.emplace_back(Boid());
    }

    std::vector<Boid> getBoids() const
    {
        return boids;
    }

    void move()
    {
        for (auto& b : boids) // access by reference to avoid copying
        {
            b.move(boids);
        }
    }

private:
    void addBoid()
    {
    }

    void deleteBoid()
    {}

    void populateFlock(const unsigned int numberOfBoid)
    {
        for (unsigned int i = 0; i < numberOfBoid; i++)
        {
            addBoid();
        }
    }
};