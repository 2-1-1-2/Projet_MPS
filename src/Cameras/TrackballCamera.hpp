#pragma once
#include <glm/glm.hpp>
#include <iostream>

class TrackballCamera {
private:
    float m_Distance;
    float m_AngleX;
    float m_AngleY;

public:
    // Constructeur
    TrackballCamera();

    void      moveFront(float delta);
    void      rotateLeft(float degrees);
    void      rotateUp(float degrees);
    glm::mat4 getViewMatrix() const;
    float     getDistance() const { return m_Distance; };
    void      printProperties() { std::cout << "m_Distance: " << m_Distance << ", m_AngleX: " << m_AngleX << ", m_AngleY: " << m_AngleY << "." << std::endl; };
};
