#include <cstdlib>
#include <vector>
#include "../Probas/Math.hpp"
#include "3D/Renderer.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
class Boid {
private:
    float                  avoidFactor;
    float                  alignmentFactor;
    float                  cohesionFactor;
    glm::vec3              position;
    glm::vec3              velocity;
    static constexpr float distAVF = 0.1;
    static constexpr float distALF = 0.4;
    static constexpr float distCOF = 0.4;

    // TODO : Mettre des limites pour les zones : (x-y) pour que ça reste dans le monde, z : pour que ce soit pas trop haut
    // TODO : Quand ça arrive aux limites (x-y) les faire "rebondir" pour pas que ça sorte des limites du mondes

public:
    Boid()

        : Boid(glm::vec3(Math::randomFloat(), Math::randomFloat(), Math::randomFloat()), glm::vec3(Math::randomFloat(), Math::randomFloat(), Math::randomFloat()), 0.5, 0.5, 0.5){};
    Boid(glm::vec3 p, glm::vec3 v, float avf, float alf, float cof);

    glm::vec3 getPos() const { return position; }
    void      move(const std::vector<Boid>& boids);
    void      wallCollision();
    void      limitSpeed();
    void      avoid(const std::vector<Boid>& boids);
    void      alignment(const std::vector<Boid>& boids);
    void      cohesion(const std::vector<Boid>& boids);
};