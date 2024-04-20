#include "Transform.hpp"

// Constructor using separate values for scale
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale)
{
    updateTransform();
}

// Constructor using uniform scale for simplicity
Transform::Transform(glm::vec3 position, glm::vec3 rotation, float uniformScale)
    : Transform(position, rotation, glm::vec3{uniformScale}){};

// Updates the transformation matrix to reflect changes in position, rotation, or scale
void Transform::updateTransform()
{
    glm::mat4 posMat   = glm::translate(glm::mat4{1.f}, position);
    glm::mat4 rotXMat  = glm::rotate(glm::mat4{1.f}, glm::radians(rotation.x), glm::vec3{1.f, 0.f, 0.f});
    glm::mat4 rotYMat  = glm::rotate(glm::mat4{1.f}, glm::radians(rotation.y), glm::vec3{0.f, 1.f, 0.f});
    glm::mat4 rotZMat  = glm::rotate(glm::mat4{1.f}, glm::radians(rotation.z), glm::vec3{0.f, 0.f, 1.f});
    glm::mat4 scaleMat = glm::scale(glm::mat4{1.f}, scale);
    transform          = posMat * rotXMat * rotYMat * rotZMat * scaleMat; // Combine all transformations
}

// Converts a direction vector into a rotation vector that points in the same direction
glm::vec3 velocityToRotationVector(const glm::vec3& velocity)
{
    glm::vec3 direction   = glm::normalize(velocity); // Normalize the velocity to get direction
    glm::vec3 up          = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::quat rotation    = glm::rotation(up, direction);             // Create a quaternion rotation from up to direction
    glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(rotation)); // Convert quaternion to Euler angles in degrees
    return eulerAngles;
}