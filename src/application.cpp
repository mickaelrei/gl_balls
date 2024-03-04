#include <iostream>

// OpenGL related includes
#include <include/glad.h>

#include <include/application.hpp>
#include <include/verlet_object.hpp>
#include <include/shader.hpp>
#include <include/solver.hpp>

// Window resize
static void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Application::Application(const std::string &title, const int width, const int height)
    : title{title}
{
    // Init GLFW
    // ---------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    // -------------
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    // Load GLAD
    // ---------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwTerminate();
        exit(-1);
    }
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::Start()
{
    // Circle shader
    Shader shader{"./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl"};

    // Circle object
    Solver solver;

    // Set polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Enable alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Render loop
    // -----------
    float before = glfwGetTime();
    float last = before;
    int maxBalls = 200;
    while (!glfwWindowShouldClose(window))
    {
        // Get dt
        float now = glfwGetTime();
        float dt = now - before;
        before = now;

        // Input
        // -----
        ProcessInput(window);

        // Update aspect ratio
        float aspectRatio = (float)Width() / (float)Height();

        // Set projection matrix
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
        shader.SetMat4("projection", projection);

        // Update title
        std::stringstream sstr;
        sstr << "Balls | " << (int)(1 / dt) << " fps";
        glfwSetWindowTitle(window, sstr.str().c_str());

        // Add object
        size_t size = solver.objects.size();
        if (now - last > .1f && (int)size < maxBalls)
        {
            last = now;
            // Create object
            VerletObject object{glm::vec2(0.0f, 0.5f), shader, 0.025f};

            // Add velocity
            float angle = (float)size / 7.f;
            float x = std::cos(angle);
            float y = -std::abs(std::sin(angle));
            object.center += glm::vec2{x, y} * .001f;

            // Add to vector
            solver.AddObject(object);
        }

        // Rendering commands
        // ------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw balls
        solver.Update(dt);
        for (VerletObject &obj : solver.objects)
        {
            obj.draw();
        }

        // Swap buffers and poll events
        // ----------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::SetTitle(const std::string &title)
{
    Application::title = title;
    glfwSetWindowTitle(window, Application::title.c_str());
}

void Application::SetWidth(const int width)
{
    glfwSetWindowSize(window, width, Height());
}

int Application::Width()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

void Application::SetHeight(const int height)
{
    glfwSetWindowSize(window, Width(), height);
}

int Application::Height()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

void Application::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}