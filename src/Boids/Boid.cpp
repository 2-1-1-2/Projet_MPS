
#include "Boid.hpp"
#include <cmath>

static constexpr float maxSpeed     = 0.006;
static constexpr float minSpeed     = 0.003;
float                  Boid::limits = 10.f;

Boid::Boid(float avf, float alf, float cof, glm::vec3 p, glm::vec3 v)
    : avoidFactor(avf)
    , alignmentFactor(alf)
    , cohesionFactor(cof)
    , position(p)
    , velocity(v)
{
    velocity /= 100;
};

void Boid::avoid(const std::vector<Boid>& boids, const float avoidMultiplier)
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

    velocity += close * avoidFactor * avoidMultiplier;
}
void Boid::alignment(const std::vector<Boid>& boids, const float alignmentMultiplier)
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
        velocity += (avgVel - velocity) * alignmentFactor * alignmentMultiplier;
    }
}

void Boid::cohesion(const std::vector<Boid>& boids, const float cohesionMultiplier)
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
        velocity += (avgPos - position) * cohesionFactor * cohesionMultiplier / static_cast<float>(200);
    }
}

void Boid::limitSpeed()
{
    const float speed = glm::length(velocity);
    // std::cout << "speed " << speed << "\n";

    if (speed > maxSpeed)
    {
        velocity *= (maxSpeed / speed);
    }
    if (speed < minSpeed)
    {
        velocity *= (minSpeed / speed);
    }
}

void Boid::move(const std::vector<Boid>& boids, BoidsMultipliers& boidsMultiplier)
{
    position += velocity * boidsMultiplier.speed;
    wallCollision();
    cohesion(boids, boidsMultiplier.cohesion);
    avoid(boids, boidsMultiplier.avoid);
    alignment(boids, boidsMultiplier.alignment);
    limitSpeed();
}

void Boid::wallCollision()
{
    const float limit = limits * 0.75; // Limite pour x, y, z

    // Collision sur l'axe x
    float newPos = position.x + velocity.x;
    if (newPos <= -limit || newPos >= limit)
    {
        position.x = std::clamp(newPos, -limit, limit); // Ajuste la position x dans les limites
        velocity.x = -velocity.x;                       // Inverse la vitesse x
    }

    // Collision sur l'axe y (assure que y reste toujours positif et dans les limites)
    newPos = position.y + velocity.y;
    if (newPos <= -.25 || newPos >= limit)
    {
        position.y = std::clamp(newPos, -.25f, limit); // Ajuste la position y entre 0 et limit
        velocity.y = -velocity.y;                      // Inverse la vitesse y
    }

    // Collision sur l'axe z
    newPos = position.z + velocity.z;
    if (newPos <= -limit || newPos >= limit)
    {
        position.z = std::clamp(newPos, -limit, limit); // Ajuste la position z dans les limites
        velocity.z = -velocity.z;                       // Inverse la vitesse z
    }

    /*
    float newPosX = position.x + velocity.x;
float newPosY = position.y + velocity.y;
float newPosZ = position.z + velocity.z;

if (abs(newPosX) > limits)
{
    newPosX = std::clamp(newPosX, -limit, limit);
}
if (abs(newPosY) > limits)
{
    newPosY = std::clamp(newPosY, -limit, limit);
}
if (abs(newPosZ) > limits)
{
    newPosZ = std::clamp(newPosZ, -limit, limit);
}

position.x = newPosX;
position.y = newPosY;
position.z = newPosZ;
    */
}

void Boid::setLimits(float limit)
{
    limits = limit - 0.75;
    std::cout << "LIMITS" << limit << "\n";
}