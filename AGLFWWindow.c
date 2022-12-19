#include <stdio.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "AFramebuffer.h"
#include "AGLFWWindow.h"

static AFramebuffer *dFBO;
static void (*frameUpdate)(void);

static void error_callback(int error, const char description[])
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    printf("Key: %d, Scanncode: %d, action: %d, mods: %d\n", key, scancode, action, mods);
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    dFBO->width = width;
    dFBO->height = height;
    frameUpdate();
}

GLFWwindow *initGLFWAndGLEW(char title[], int width, int height, AFramebuffer *dfbo, void (*frameUpdateFunction)(void))
{
    frameUpdate = frameUpdateFunction;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        printf_s("Initiliziation failed! Terminating Program!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(640, 480, title, NULL, NULL);
    if (!window)
    {
        printf_s("Window initilization failed! Program will probably terminate");
    }
    dFBO = dfbo;
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();

    dfbo->width = width;
    dfbo->height = height;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&dfbo->fbo);

    return window;
}
