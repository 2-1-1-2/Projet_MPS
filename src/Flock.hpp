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
    std::vector<Boid> flock;

public:
    Flock(const unsigned int number)
    {
        for (unsigned int i = 0; i < number; i++)
            flock.emplace_back(Boid{});
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