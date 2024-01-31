
#include "Boid.hpp"
#include <iostream>
#include "glm/fwd.hpp"

void Boid::avoid(const std::vector<Boid>& boids)
{
    for (const Boid& other : boids)
    {
        if (&other != this)
        {
            double distance = glm::length(position - other.position);
            if (distance < avoidFactor)
            {
                velocity += (position - other.position);
            }
        }
    }
}
void Boid::alignment(const std::vector<Boid>& boids)
{
    glm::vec2 avgVel(0, 0);
    int       count = 0;

    for (const Boid other : boids)
    {
        if (&other != this)
        {
            if (glm::length(position - other.position) < alignmentFactor)
            {
                avgVel += other.velocity;
                count++;
            }
        }
    }

    if (count > 0)
    {
        avgVel /= count;
        velocity += (avgVel - velocity) * 0.1f;
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
            if (glm::length(position - other.position) < cohesionFactor)
            {
                avgPos += other.position;
                count++;
            }
        }
    }

    if (count > 0)
    {
        avgPos /= count;
        velocity += (avgPos - position) * 0.1f;
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
        std::cout << velocity.x << "\n";
        std::cout << velocity.y << "\n";
    }
}

void Boid::move(const std::vector<Boid>& boids)
{
    wallCollision();
    alignment(boids);
    cohesion(boids);
    avoid(boids);
    limitSpeed();
    position += velocity;
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