#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "AGLFWWindow.h"
#include "aVAO.h"
#include "aShader.h"
#include "aFramebuffer.h"
#include "aScene.h"
#include "vec3.h"
#include "aArrayList.h"
#include "aList.h"
#include "vec2.h"
#include "vec4.h"

static AFramebuffer dfbo = {0, 0, 0, 0};
static GLFWwindow *window;
static AScene *scene;

static void prepFrameCycle()
{
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);
    glClearColor(0.0f, 0.0f, 0.2f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
}

static void drawFrame()
{
    prepFrameCycle();
    AList *vaoList = scene->vaos;
    VAO **vaos = (VAO **)vaoList->data;
    glUseProgram(scene->shader->prog);
    glBindVertexArray(vaos[0]->glVAO);

    for (unsigned int i = 0; i < vaoList->size; i++)
    {
        glDrawElements(GL_TRIANGLES, vaos[0]->ibo->size, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    dfbo.width = width;
    dfbo.height = height;
    drawFrame();
}

int main(int argc, char *argv[])
{
    window = initGLFWAndGLEW("OpenGL Application", 512, 512, &dfbo);

    // AFramebuffer fbo = createAFramebuffer(dfbo.width / 4, dfbo.height / 4);
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);

    printf_s("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf_s("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf_s("Vendor: %s\n", glGetString(GL_VENDOR));

    unsigned int ibo[] = {0, 1, 2};
    vec2 pbo[] = {{0.0f, 0.5f}, {-0.5f, -0.5f}, {0.5f, -0.5f}};
    vec4 vcbo[] = {{1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}};
    float coverage[] = {1.0f, 1.0f, 1.0f};

    VAO *vao = createVAOFromData(3, 3, ibo, pbo, vcbo, coverage);
    printVAO(vao);

    AShader *sha = createShader("shader/basicVert.glsl", "shader/basicFrag.glsl");

    scene = createAScene();
    scene->shader = sha;
    addToAList(scene->vaos, vao);

    printf_s("Begin Loop\n");
    clock_t start_t, end_t;
    double total_t;
    unsigned long long step = 0;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {
        start_t = clock();
        printf_s("Begin Step: %llu\n", step);
        glfwPollEvents();
        drawFrame();
        step++;

        end_t = clock();
        total_t = (double)(end_t - start_t);

        char title[32];
        snprintf(title, 32, "Time: %dms, FPS: %d", (int)(total_t), (int)(1000.0 / total_t));
        glfwSetWindowTitle(window, title);
    }

    printf_s("Destroy Scene\n");
    destroyScene(scene);

    printf("Destroy GLTF window\n");
    glfwDestroyWindow(window);

    printf("Destroy GLTF\n");
    glfwTerminate();

    printf("terminate");
    return 0;
}