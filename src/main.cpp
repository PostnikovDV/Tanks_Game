#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowCallBack(GLFWwindow* windowPtr, int width, int heigth)
{
    g_windowSizeX = width;
    g_windowSizeY = heigth;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallBack(GLFWwindow* windowPtr, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(windowPtr, GL_TRUE);
    }
}



int main(void)
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
    GLFWwindow* windowPtr = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "T4nks G4me", nullptr, nullptr);
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

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    glClearColor(10010, 1, 10, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(windowPtr))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(windowPtr);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}