#pragma once
#include <cassert>
#include <vector>
#include "Boid.hpp"
#include "Primitives/Object3D.hpp"

class Flock {
private:
    std::vector<Boid>        _boids;
    std::vector<std::string> _skinList = {"_red", "_orange", "_blue", "_green", "_blue", "_grey", "_monochrome"};

    Object3D _object3D_high;
    Object3D _object3D_mid;
    Object3D _object3D_low;

    void addBoid();
    void deleteBoid();

public:
    explicit Flock(unsigned int number);

    void move(BoidsMultipliers& boidsMultiplier);
    void populateFlock(unsigned int number);
    void deleteBoids(unsigned int number);
    int  getSize();
    void regulateBoids(int _nb_boids);
    void initializeGUI();
    void setLimits(float limit);

    std::vector<Boid> getBoids() const { return _boids; }
    Object3D&         getObject3D(const int LoD)
    {
        if (LoD == 3)
            return _object3D_high;
        else if (LoD == 2)
            return _object3D_mid;
        else
            return _object3D_low;
    };
};