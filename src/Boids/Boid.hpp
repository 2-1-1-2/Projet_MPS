#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Maths/Math.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"

struct BoidsMultipliers {
    float speed     = 10.f;
    float avoid     = 0.005f;
    float alignment = 1.192f;
    float cohesion  = .0f;
};

class Boid {
private:
    float                  avoidFactor;
    float                  alignmentFactor;
    float                  cohesionFactor;
    glm::vec3              position;
    glm::vec3              velocity;
    static float           limits;
    static constexpr float distAVF = .4;
    static constexpr float distALF = 1;
    static constexpr float distCOF = 2;

public:
    Boid()

        : Boid(0.5, 0.5, 0.5, glm ::vec3(Math::randUniformC(-10, 10), Math::randUniformC(-10, 10), Math::randUniformC(-10, 10)), glm::vec3(Math::randUniformC(-1, 1), Math::randUniformC(-1, 1), Math::randUniformC(-1, 1))){};
    Boid(float avf, float alf, float cof, glm::vec3 p, glm::vec3 v);

    glm::vec3 getPos() const { return position; }
    void      move(const std::vector<Boid>& boids, BoidsMultipliers& boidsMultiplier);
    void      wallCollision();
    void      limitSpeed();
    void      avoid(const std::vector<Boid>& boids, float avoidMultiplier);
    void      alignment(const std::vector<Boid>& boids, float alignmentMultiplier);
    void      cohesion(const std::vector<Boid>& boids, float cohesionMultiplier);
    void      setLimits(float limit);
};