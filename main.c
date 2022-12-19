#include <stdio.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "AGLFWWindow.h"
#include "VAO.h"
#include "AShader.h"
#include "AFramebuffer.h"
#include "AScene.h"

static AFramebuffer dfbo = {0, 0, 0, 0};
static GLFWwindow *window;
static AScene scene;

static void prepFrameCycle()
{
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);
    glClearColor(0.0f, 0.0f, 0.2f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void drawFrame()
{
    prepFrameCycle();
    AList vaoList = scene.vaos;
    VAO **vaos = (VAO **)vaoList.data;
    glUseProgram(scene.shader.prog);
    glBindVertexArray(vaos[0]->glVAO);

    for (unsigned int i = 0; i < vaoList.size; i++)
    {
        glDrawElements(GL_TRIANGLES, vaos[0]->numIndices, GL_UNSIGNED_INT, 0);
    }

    printf("width: %d, height: %d \n", dfbo.width, dfbo.height);

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
}

int main(int argc, char *argv[])
{
    window = initGLFWAndGLEW("OpenGL Application", 512, 512, &dfbo, drawFrame);

    // AFramebuffer fbo = createAFramebuffer(dfbo.width / 4, dfbo.height / 4);
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDER));

    unsigned int ibo[] = {0, 1, 2};
    float pbo[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
    float vcbo[] = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
    float coverage[] = {1.0f, 1.0f, 1.0f, 1.0f};

    VAO vao = cretateVAOByData(3, 3, ibo, pbo, vcbo, coverage);

    AShader sha = createShader("AShader/basicVert.glsl", "AShader/basicFrag.glsl");

    scene.shader = sha;
    scene.vaos = createAList();
    addToList(&scene.vaos, &vao);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        drawFrame();
    }

    destroyVAO(&vao);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}