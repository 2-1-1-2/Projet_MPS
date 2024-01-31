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
    static constexpr double maxSpeed = 0.006;
    static constexpr double minSpeed = 0.003;
    static constexpr double distAVF  = 0.1;
    static constexpr double distALF  = 0.4;
    static constexpr double distCOF  = 0.4;

public:
    Boid()
        : Boid(glm::vec2(Math::randomDouble(), Math::randomDouble()), glm::vec2(Math::randomDouble(), Math::randomDouble()), 0.5, 0.5, 0.5){};

    Boid(glm::vec2 p, glm::vec2 v, double avf, double alf, double cof)
        : avoidFactor(avf), alignmentFactor(alf), cohesionFactor(cof), position(p), velocity(v)
    {
        position *= glm::vec2(Math::randomSign(), Math::randomSign());
        velocity /= 100;

        velocity *= glm::vec2(Math::randomSign(), Math::randomSign());
    };

    glm::vec2 getPos() const { return position; }

    void move(const std::vector<Boid>& boids);

    void wallCollision();

    void avoid(const std::vector<Boid>& boids);
    void alignment(const std::vector<Boid>& boids);
    void cohesion(const std::vector<Boid>& boids);

    void limitSpeed();
    ~Boid() = default;
};