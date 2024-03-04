#include <iostream>
#include <include/verlet_object.hpp>

VerletObject::VerletObject(glm::vec2 position, Shader shader, const float radius)
    : Circle{position, radius, shader},
      oldPosition{position},
      acceleration{} {}

void VerletObject::UpdatePosition(float dt)
{
    // Get velocity from both positions
    const glm::vec2 velocity = center - oldPosition;

    // Save current position
    oldPosition = center;

    // Verlet integration
    center = center + velocity + acceleration * dt * dt;

    // Reset acceleration
    acceleration = {};
}

void VerletObject::Accelerate(glm::vec2 acc)
{
    acceleration += acc;
}
