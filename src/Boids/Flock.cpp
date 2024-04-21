#include "Flock.hpp"

Flock::Flock(const unsigned int number)
    : _boids(number), _object3D("WillOWisp", "3D.vs.glsl", "tex3D.fs.glsl", _skinList[p6::random::number(0, 7)]) {}

void Flock::move()
{
    for (auto& b : _boids)
        b.move(_boids);
}

void Flock::addBoid()
{
    _boids.emplace_back(Boid());
}

void Flock::deleteBoid()
{
    _boids.pop_back();
}

void Flock::populateFlock(const unsigned int number)
{
    assert(number > 0);
    for (unsigned int i = 0; i < number; i++)
        addBoid();
}

void Flock::deleteBoids(const unsigned int number)
{
    assert(number > 0);
    for (unsigned int i = 0; i < number; i++)
        deleteBoid();
}