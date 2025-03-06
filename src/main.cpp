#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/vec2.hpp"
#include <iostream>

#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

#include <chrono>
#include "Game/Game.h"


glm::ivec2 g_windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> s_game(std::make_unique<Game>(g_windowSize));


void glfwWindowCallBack(GLFWwindow* windowPtr, int width, int heigth)
{
    g_windowSize.x = width;
    g_windowSize.y = heigth;

    const float aspect_ratio = 13.f / 14.f;

    unsigned int viewPortWidht = g_windowSize.x;
    unsigned int viewPortHeight = g_windowSize.y;

    unsigned int offsetLeft{ 0 };
    unsigned int offsetBottom{ 0 };

    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > aspect_ratio)
    {
        viewPortWidht = static_cast<unsigned int>(g_windowSize.y * aspect_ratio);

        offsetLeft = (g_windowSize.x - viewPortWidht) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(g_windowSize.x / aspect_ratio);

        offsetBottom = (g_windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortWidht, viewPortHeight, offsetLeft, offsetBottom);
}

void glfwKeyCallBack(GLFWwindow* windowPtr, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(windowPtr, GL_TRUE);
    }

    s_game->setKey(key, action);

}

int main(int argc, char** argv)
{
    if (!glfwInit()) //Initialize the library 
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* windowPtr = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "T4nks G4me", nullptr, nullptr);
    if (!windowPtr)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(windowPtr, glfwWindowCallBack);
    glfwSetKeyCallback(windowPtr, glfwKeyCallBack);

    glfwMakeContextCurrent(windowPtr); // Make the window's context current

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    std::cout << "OpenGL version " << RenderEngine::Renderer::getVersionStr() << std::endl;

    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);

    {
        ResourceManager::setExecutablePath(argv[0]);

        bool gameActive =  s_game->init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(windowPtr))
        {
           
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;

            s_game->update(duration);
            /* Render here */
            RenderEngine::Renderer::setClear();

            s_game->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(windowPtr);

            /* Poll for and process events */
            glfwPollEvents();
        }
        s_game = nullptr;
        ResourceManager::unloadAllResources();
    }

    glfwTerminate();
    return 0;
}