#pragma once
#include <cassert>
#include <vector>
#include "Boid.hpp"
#include "Primitives/Object3D.hpp"

class Flock {
private:
    std::vector<Boid>        _boids;
    std::vector<std::string> _skinList = {"_red", "_orange", "_blue", "_green", "_blue", "_grey", "_monochrome"};

    Object3D _object3D;

    void addBoid();
    void deleteBoid();
    void populateFlock(const unsigned int number);
    void deleteBoids(const unsigned int number);

public:
    explicit Flock(const unsigned int number);

    void move();

    std::vector<Boid> getBoids() const { return _boids; }
    Object3D&         getObject3D() { return _object3D; };
};