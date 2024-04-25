#include "Flock.hpp"
#include "Boids/Boid.hpp"

Flock::Flock(const unsigned int number)
    : _boids(number), _object3D_high("WillOWisp", "base3D.vs.glsl", "base3D.fs.glsl", _skinList[p6::random::number(0, 7)], "_high"), _object3D_mid("WillOWisp", "base3D.vs.glsl", "base3D.fs.glsl", _skinList[p6::random::number(0, 7)], "_mid"), _object3D_low("WillOWisp", "base3D.vs.glsl", "base3D.fs.glsl", _skinList[p6::random::number(0, 7)], "_low") {}

void Flock::move(BoidsMultipliers& boidsMultiplier)
{
    for (auto& b : _boids)
        b.move(_boids, boidsMultiplier);
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

int Flock::getSize()
{
    return _boids.size();
}

void Flock::regulateBoids(int _nb_boids)
{
    if (getSize() > _nb_boids)
    {
        deleteBoids(getSize() - _nb_boids);
    }
    else if (getSize() < _nb_boids)
    {
        populateFlock(_nb_boids);
    }
}
void Flock::setLimits(float limit)
{
    for (auto& boid : _boids)
    {
        boid.setLimits(limit);
    }
}