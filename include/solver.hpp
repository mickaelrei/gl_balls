#pragma once
#include <vector>
#include <include/verlet_object.hpp>

class Solver
{
public:
    void AddObject(VerletObject object);
    void Update(float dt);

    glm::vec2 gravity = {0.0f, -5.0f};
    std::vector<VerletObject> objects;

private:
    void UpdatePositions(float dt);
    void ApplyGravity();
    void ApplyConstraints();
    void SolveCollisions();
};