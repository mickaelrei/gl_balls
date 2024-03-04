#include <iostream>
#include <include/solver.hpp>

void Solver::AddObject(VerletObject object)
{
    objects.push_back(object);
}

void Solver::Update(float dt)
{
    const int subSteps = 8;
    const float subDt = dt / (float)subSteps;
    for (int i = 0; i < subSteps; ++i)
    {
        ApplyGravity();
        ApplyConstraints();
        SolveCollisions();
        UpdatePositions(subDt);
    }
}

void Solver::UpdatePositions(float dt)
{
    for (VerletObject &object : objects)
    {
        object.UpdatePosition(dt);
    }
}

void Solver::ApplyGravity()
{
    for (VerletObject &object : objects)
    {
        object.Accelerate(gravity);
    }
}

void Solver::ApplyConstraints()
{
    glm::vec2 constraintPosition = {0.f, 0.f};
    const float constraintRadius = 1.0f;

    for (VerletObject &object : objects)
    {
        glm::vec2 toObj = object.center - constraintPosition;
        const float dist = glm::length(toObj);
        if (dist > constraintRadius - object.radius)
        {
            glm::vec2 norm = toObj / dist;
            object.center = constraintPosition + norm * (constraintRadius - object.radius);
        }
    }
}

void Solver::SolveCollisions()
{
    // TODO: This is O(n²), very inefficient. Use threads to divide work
    size_t size = objects.size();
    for (size_t i = 0; i < size; ++i)
    {
        VerletObject &object0 = objects[i];
        for (size_t j = i + 1; j < size; ++j)
        {
            // Get vector between both objects
            VerletObject &object1 = objects[j];
            glm::vec2 collAxis = object0.center - object1.center;

            // Check for distance
            float minDist = object0.radius + object1.radius;
            float dist = glm::length(collAxis);
            if (dist < minDist)
            {
                glm::vec2 norm = collAxis / dist;
                float delta = minDist - dist;
                object0.center += 0.5f * norm * delta;
                object1.center -= 0.5f * norm * delta;
            }
        }
    }
}
