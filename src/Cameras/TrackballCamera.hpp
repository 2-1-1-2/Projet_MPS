#pragma once
#include <glm/glm.hpp>
#include <iostream>

class TrackballCamera {
private:
    float      m_Distance;
    float      m_AngleX;
    float      m_AngleY;
    glm::vec3* m_Target;

public:
    // Constructeur
    TrackballCamera(glm::vec3* target);

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
    float     getDistance() const { return m_Distance; };
    float     getAngleX() const { return m_AngleX; };
    float     getAngleY() const { return m_AngleY; };

    void setTarget(glm::vec3* target) { m_Target = target; };

    void printProperties() { std::cout << "m_Distance: " << m_Distance << ", m_AngleX: " << m_AngleX << ", m_AngleY: " << m_AngleY << "." << std::endl; };
};
