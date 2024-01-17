
class Boid {
    /*
    - Séparation
    - Alignement
    - Cohésion

    - position : x
    - vitesse, y (z)

    - function déplacement
    - s

    */

private:
    double avoidFactor;
    double alignementFactor;
    double cohesionFactor;
    double posX;
    double posY;
    double velX;
    double velY;
    void   move();

public:
    Boid()
    {
    }
};