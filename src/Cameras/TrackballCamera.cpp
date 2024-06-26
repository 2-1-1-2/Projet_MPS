#include "TrackballCamera.hpp"

TrackballCamera::TrackballCamera(glm::vec3* target)
    : m_Target(target), m_Distance(3.f), m_AngleX(0.0f), m_AngleY(0.0f) {}

void TrackballCamera::moveFront(float delta)
{
    m_Distance -= delta;
}

void TrackballCamera::rotateLeft(float degrees)
{
    m_AngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_AngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix           = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -m_Distance));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_AngleX), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix           = glm::rotate(viewMatrix, glm::radians(m_AngleY), glm::vec3(0.0f, 1.0f, 0.0f));
    if (m_Target)
    {
        glm::vec3 positionToFollow{m_Target->x, 0.f, m_Target->z};
        viewMatrix = glm::translate(viewMatrix, -positionToFollow);
    }
    return viewMatrix;
}