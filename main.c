#include <stdio.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "AGLFWWindow.h"
#include "aVAO.h"
#include "aShader.h"
#include "aFramebuffer.h"
#include "aScene.h"
#include "vec3.h"
#include "aArrayList.h"
#include "vec2.h"
#include "vec4.h"

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
        glDrawElements(GL_TRIANGLES, vaos[0]->ibo.size, GL_UNSIGNED_INT, 0);
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
    vec2 pbo[] = {{0.0f, 0.5f}, {-0.5f, -0.5f}, {0.5f, -0.5f}};
    vec4 vcbo[] = {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
    float coverage[] = {1.0f, 1.0f, 1.0f};

    VAO vao = createVAOFromData(3, 3, ibo, pbo, vcbo, coverage);
    printVAO(&vao);

    AShader sha = createShader("shader/basicVert.glsl", "shader/basicFrag.glsl");

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