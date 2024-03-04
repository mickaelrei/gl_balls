#pragma once

#include <GLFW/glfw3.h>

#include <string>

class Application
{
public:
    // Constructor
    Application(const std::string &title, const int width, const int height);
    // Destructor
    ~Application();

    // Start app
    void Start();

    // Set window title
    void SetTitle(const std::string &title);

    // Get window width
    int Width();

    // Set window width
    void SetWidth(const int width);

    // Get window height
    int Height();

    // Set window height
    void SetHeight(const int height);

private:
    // Callback for input processing
    void ProcessInput(GLFWwindow *window);

    // GLFW Window
    GLFWwindow *window;

    // Window title
    std::string title;
};