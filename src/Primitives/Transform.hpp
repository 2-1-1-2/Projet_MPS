#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

/// Manages transformations for a 3D object
class Transform {
private:
    glm::vec3 position; // Position in 3D space
    glm::vec3 rotation; // Euler angles for rotation (in degrees)
    glm::vec3 scale;    // Scale factors

    glm::mat4 transform; // Computed transformation matrix

    void updateTransform(); // Updates the transformation matrix based on position, rotation, and scale

public:
    // Constructors initialize transformations with default parameters
    explicit Transform(glm::vec3 position = glm::vec3{0.f}, glm::vec3 rotation = glm::vec3{0.f}, glm::vec3 scale = glm::vec3{1.f});
    Transform(glm::vec3 position, glm::vec3 rotation, float uniformScale = 1.f);

    // Returns the transformation matrix
    glm::mat4 getTransform() const { return transform; };
};

glm::vec3 velocityToRotationVector(const glm::vec3& velocity);