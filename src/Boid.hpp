#include <cstdlib>
#include <vector>
#include "Math.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
class Boid {
private:
    double                  avoidFactor;
    double                  alignmentFactor;
    double                  cohesionFactor;
    glm::vec2               position;
    glm::vec2               velocity;
    static constexpr double maxSpeed = 0.01;

public:
    Boid()
        : Boid(glm::vec2(Math::randomDouble(), Math::randomDouble()), glm::vec2(Math::randomDouble(), Math::randomDouble()), Math::randomDouble(), Math::randomDouble(), Math::randomDouble()){};

    Boid(glm::vec2 p, glm::vec2 v, double avf, double alf, double cof)
        : avoidFactor(avf), alignmentFactor(alf), cohesionFactor(cof), position(p), velocity(v)
    {
        position *= glm::vec2(Math::randomSign(), Math::randomSign());
        velocity /= 100;
        avoidFactor /= 10;
        alignmentFactor /= 10;
        cohesionFactor /= 10;
        velocity *= glm::vec2(Math::randomSign(), Math::randomSign());
    };

    glm::vec2 getPos() const { return position; }

    void move(const std::vector<Boid>& boids)
    {
        wallCollision();
        avoid(boids);
        alignment(boids);
        cohesion(boids);
        limitSpeed();
        position += velocity;
    }

    void wallCollision()
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

    void avoid(const std::vector<Boid>& boids);
    void alignment(const std::vector<Boid>& boids);
    void cohesion(const std::vector<Boid>& boids);

    void limitSpeed();
};