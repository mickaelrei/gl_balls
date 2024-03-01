#ifndef CIRCLE_H
#define CIRCLE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

const unsigned int __indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

class Circle
{
public:
    // the program ID
    unsigned int ID;

    // Circle radius
    float radius;

    // Circle pos
    float centerX, centerY;

    // GL Objects
    unsigned int VBO, VAO, EBO;

    // constructor
    Circle(const float _centerX, const float _centerY, const float _radius, float aspectRatio)
        : radius{_radius},
          centerX{_centerX},
          centerY{_centerY}
    {
        // Setup vertex data (and buffer) and configure vertex attributes
        // --------------------------------------------------------------
        const float left = centerX - radius / aspectRatio;
        const float right = centerX + radius / aspectRatio;
        const float top = centerY - radius;
        const float bottom = centerY + radius;
        float vertices[] = {
            // positions
            left, bottom, 0.0f,  // bottom left
            left, top, 0.0f,     // top left
            right, top, 0.0f,    // top right
            right, bottom, 0.0f, // bottom right
        };

        // Create vertex objects
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the array (VAO) first
        glBindVertexArray(VAO);

        // Then bind and set the buffer (VBO)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Then bind and set the elements buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(__indices), __indices, GL_STATIC_DRAW);
        
        // How to interpret the vertex data (layout location on vertex shader)
        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

        // Unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

#endif // CIRCLE_H