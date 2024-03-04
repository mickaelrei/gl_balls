#include <include/circle.hpp>

#include <include/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default vertices for quad
const float __vertices[] = {
    // positions
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f,  // top left
    1.0f, 1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,  // bottom right
};

// Default indices for quad
const unsigned int __indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

Circle::Circle(glm::vec2 center, const float radius, Shader shader)
    : radius{radius},
      center{center},
      shader{shader}
{
    // Create vertex objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the array (VAO) first
    glBindVertexArray(VAO);

    // Then bind and set the buffer (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(__vertices), __vertices, GL_STATIC_DRAW);

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

void Circle::draw()
{
    shader.Use();

    // Set model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(center.x, center.y, 0.0f));
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
    shader.SetMat4("model", model);

    // Set radius
    shader.SetFloat("radius", radius);

    // Draw elements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}