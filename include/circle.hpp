#ifndef CIRCLE_H
#define CIRCLE_H

#include <include/shader.hpp>

class Circle
{
public:
    // Constructor
    Circle(glm::vec2 center, const float radius, Shader shader);

    // the program id
    unsigned int id;

    // Circle radius
    float radius;

    // Circle pos
    glm::vec2 center;

    // GL Objects
    unsigned int VBO, VAO, EBO;

    // Circle shader
    Shader shader;

    // Draw circle
    void draw();
};

#endif // CIRCLE_H