#include <cstdlib>
#include <vector>
#include "Math.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
class Boid {
private:
    float                  avoidFactor;
    float                  alignmentFactor;
    float                  cohesionFactor;
    glm::vec2              position;
    glm::vec2              velocity;
    static constexpr float distAVF = 0.1;
    static constexpr float distALF = 0.4;
    static constexpr float distCOF = 0.4;

public:
    Boid()
        : Boid(glm::vec2(Math::randomFloat(), Math::randomFloat()), glm::vec2(Math::randomFloat(), Math::randomFloat()), 0.5, 0.5, 0.5){};
    Boid(glm::vec2 p, glm::vec2 v, float avf, float alf, float cof);

    glm::vec2 getPos() const { return position; }
    void      move(const std::vector<Boid>& boids);
    void      wallCollision();
    void      limitSpeed();
    void      avoid(const std::vector<Boid>& boids);
    void      alignment(const std::vector<Boid>& boids);
    void      cohesion(const std::vector<Boid>& boids);
};