#pragma once

#include <include/circle.hpp>
#include <glm/glm.hpp>

class VerletObject : public Circle
{
public:
    VerletObject() = default;
    VerletObject(glm::vec2 position, Shader shader, const float radius = 0.15f);

    glm::vec2 oldPosition;
    glm::vec2 acceleration;

    void UpdatePosition(float dt);
    void Accelerate(glm::vec2 acc);
};
