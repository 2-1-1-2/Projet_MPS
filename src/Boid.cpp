
#include "Boid.hpp"
#include <iostream>
#include "glm/fwd.hpp"

void Boid::avoid(const std::vector<Boid>& boids)
{
    glm::vec2 close(0, 0);

    for (const Boid other : boids)
    {
        if (&other != this)
        {
            if (glm::length(position - other.position) < distAVF)
            {
                close += position - other.position;
            }
        }
    }

    velocity += close * static_cast<float>(avoidFactor);
}
void Boid::alignment(const std::vector<Boid>& boids)
{
    glm::vec2 avgVel(0, 0);
    int       count = 0;

    for (const Boid other : boids)
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
        velocity += (avgVel - velocity) * static_cast<float>(alignmentFactor);
    }
}
void Boid::cohesion(const std::vector<Boid>& boids)
{
    glm::vec2 avgPos(0, 0);
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
        velocity += (avgPos - position) * static_cast<float>(cohesionFactor) / static_cast<float>(200);
    }
}

// TODO(tanya): Bof à revoir
void Boid::limitSpeed()
{
    float speed = glm::length(velocity);
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