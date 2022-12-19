#include <stdio.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "AGLFWWindow.h"
#include "VAO.h"
#include "shader.h"

int main(int argc, char *argv[])
{
    GLFWwindow *window = initGLFWAndGLEW("OpenGL Application", 512, 512);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDER));

    unsigned int ibo[] = {0, 1, 2};
    float pbo[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
    float vcbo[] = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
    float coverage[] = {1.0f, 1.0f, 1.0f, 1.0f};

    VAO vao = cretateVAOByData(3, 3, ibo, pbo, vcbo, coverage);

    shader sha = createShader("shader/basicVert.glsl", "shader/basicFrag.glsl");
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        glUseProgram(sha.prog);
        glBindVertexArray(vao.glVAO);

        glDrawElements(GL_TRIANGLES, vao.numIndices, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    destroyVAO(&vao);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}