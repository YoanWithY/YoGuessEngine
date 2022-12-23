#include <stdio.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "AFramebuffer.h"
#include "AGLFWWindow.h"

static void error_callback(int error, const char description[])
{
    printf_s("GLTF Error: %s\n", description);
}

void glm(GLenum source,
         GLenum type,
         GLuint id,
         GLenum severity,
         GLsizei length,
         const GLchar *message,
         const void *userParam)
{
    printf_s("OpenGL Message: %s\n", message);
}

GLFWwindow *initGLFWAndGLEW(char title[], int width, int height, AFramebuffer *dfbo, void (*key_callback)(GLFWwindow *window, int key, int scancode, int action, int mods))
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        printf_s("Initiliziation failed! Terminating Program!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        printf_s("Window initilization failed! Program will probably terminate");
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glm, NULL);

    dfbo->width = width;
    dfbo->height = height;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&dfbo->fbo);

    return window;
}
