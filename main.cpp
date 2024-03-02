#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cmath>

#include "shader.hpp"
#include "circle.hpp"

int windowWidth = 1200;
int windowHeight = 600;

// Window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

// Input
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float getAspectRatio()
{
    return (float)windowWidth / (float)windowHeight;
}

int main()
{
    // Init GLFW
    // ---------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    // -------------
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Balls", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    // ---------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    // Aspect ratio
    float aspectRatio = getAspectRatio();

    // Shader and circle
    Shader shader{"./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl"};
    // Circle circle{-0.5f, 0.5f, 0.5f, aspectRatio};
    Circle circles[4] = {
        Circle{-0.5f, -0.5f, 0.5f, aspectRatio},
        Circle{0.35f, 0.2f, 0.15f, aspectRatio},
        Circle{-0.6f, -0.3f, 0.25f, aspectRatio},
        Circle{0.8f, 0.8f, 0.05f, aspectRatio},
    };

    // Set polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Render loop
    // -----------
    float before = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        // Input
        // -----
        processInput(window);

        // Update aspect ratio
        aspectRatio = getAspectRatio();

        // Get dt
        float now = glfwGetTime();
        float dt = now - before;
        before = now;

        // Update title
        std::stringstream sstr;
        sstr << "Balls | " << (int)(1 / dt) << " fps";
        glfwSetWindowTitle(window, sstr.str().c_str());

        // Move balls in circular motion
        for (int i = 0; i < 4; ++i)
        {
            float div = (float)(i + 1);
            Circle &circle = circles[i];
            circle.centerX = -0.5f + 0.25f * div + std::cos(now / div) / aspectRatio * 0.5f;
            circle.centerY = std::sin(now / div) * 0.5f;
            circle.radius = std::abs(std::sin(now / div * .4f)) * 0.25f + 0.15f / div;
        }

        // Rendering commands
        // ------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw balls
        shader.use();
        for (int i = 0; i < 4; ++i)
        {
            Circle circle = circles[i];
            shader.setFloat2("center", circle.centerX, circle.centerY);
            shader.setFloat("radius", circle.radius);
            shader.setFloat("aspectRatio", aspectRatio);
            circle.draw();
        }

        // Swap buffers and poll events
        // ----------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
