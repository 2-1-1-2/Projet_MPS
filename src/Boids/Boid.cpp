
#include "Boid.hpp"
#include <iostream>
#include "glm/fwd.hpp"

static constexpr float maxSpeed = 0.006;
static constexpr float minSpeed = 0.003;

Boid::Boid(glm::vec3 p, glm::vec3 v, float avf, float alf, float cof)
    : avoidFactor(avf), alignmentFactor(alf), cohesionFactor(cof), position(p), velocity(v)
{
    position *= glm::vec3(Math::randomSign(), Math::randomSign(), Math::randomSign());
    velocity /= 100;

    velocity *= glm::vec3(Math::randomSign(), Math::randomSign(), Math::randomSign());
};

void Boid::avoid(const std::vector<Boid>& boids)
{
    glm::vec3 close(0, 0, 0);

    for (const Boid& other : boids)
    {
        if (&other != this)
        {
            if (glm::length(position - other.position) < distAVF)
            {
                close += position - other.position;
            }
        }
    }

    velocity += close * avoidFactor;
}
void Boid::alignment(const std::vector<Boid>& boids)
{
    glm::vec3 avgVel(0, 0, 0);
    int       count = 0;

    for (const Boid& other : boids)
    {
        if (&other != this)
        {
            if (glm::length(position - other.position) < distALF)
            {
                avgVel += other.velocity;
                count++;
            }
        }
    }

    if (count > 0)
    {
        avgVel /= count;
        velocity += (avgVel - velocity) * alignmentFactor;
    }
}

void Boid::cohesion(const std::vector<Boid>& boids)
{
    glm::vec3 avgPos(0, 0, 0);
    int       count = 0;

    for (const Boid& other : boids)
    {
        if (&other != this)
        {
            if (glm::length(position - other.position) < distCOF)
            {
                avgPos += other.position;
                count++;
            }
        }
    }

    if (count > 0)
    {
        avgPos /= count;
        velocity += (avgPos - position) * cohesionFactor / static_cast<float>(200);
    }
}

void Boid::limitSpeed()
{
    const float speed = glm::length(velocity);
    std::cout << "speed " << speed << "\n";

    if (speed > maxSpeed)
    {
        velocity *= (maxSpeed / speed);
    }
    if (speed < minSpeed)
    {
        velocity *= (minSpeed / speed);
    }
}

void Boid::move(const std::vector<Boid>& boids)
{
    position += velocity;
    wallCollision();
    cohesion(boids);
    avoid(boids);
    alignment(boids);
    limitSpeed();
}

void Boid::wallCollision()
{
    if (std::abs((position + velocity).x) >= 1)
    {
        velocity.x = -velocity.x;
    }
    if (std::abs((position + velocity).y) >= 1)
    {
        velocity.y = -velocity.y;
    }
}