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
#include "basicShape.h"
#include "aList.h"
#include "vec2.h"
#include "vec4.h"
#include "mat3.h"

static AFramebuffer dfbo = {0, 0, 0, 0};
static GLFWwindow *window;
static AScene *scene;
BasicShape *selectedShape = NULL;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    printf_s("Key: %d, Scanncode: %d, action: %d, mods: %d\n", key, scancode, action, mods);

    if (selectedShape != NULL)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_W:
            {
                selectedShape->translation->y--;
                break;
            }

            case GLFW_KEY_A:
            {
                selectedShape->translation->x--;
                break;
            }

            case GLFW_KEY_S:
            {
                selectedShape->translation->y++;
                break;
            }

            case GLFW_KEY_D:
            {
                selectedShape->translation->x++;
                break;
            }

            case GLFW_KEY_Q:
            {
                selectedShape->rotation += 0.1f;
                break;
            }

            case GLFW_KEY_E:
            {
                selectedShape->rotation += -0.1f;
                break;
            }

            default:
                break;
            }
        }
    }
}

static void prepFrameCycle()
{
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

mat3 tMat;

static void drawFrame()
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    prepFrameCycle();
    AList *vaoList = scene->basicShapes;
    BasicShape **basicShapes = (BasicShape **)vaoList->data;
    glUseProgram(scene->shader->prog);
    AShader *shader = scene->shader;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->glAALUT);

    for (unsigned int i = 0; i < vaoList->size; i++)
    {
        BasicShape *shape = basicShapes[i];
        glBindVertexArray(shape->vao->glVAO);
        makeRotatationTranslationTransformation(tMat, shape->rotation, shape->translation);
        glUniform1f(shader->glRotAdd, shape->rotation / 1.57079632679f);
        glUniformMatrix3fv(shader->glTMat, 1, GL_TRUE, (const GLfloat *)tMat);
        glDrawElements(GL_TRIANGLES, shape->vao->numIndices, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(window);
    end_t = clock();
    total_t = (double)(end_t - start_t);
    char title[32];
    snprintf(title, 32, "Time: %dms, FPS: %d", (int)(total_t), (int)(1000.0 / total_t));
    glfwSetWindowTitle(window, title);
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    dfbo.width = width;
    dfbo.height = height;
    glUseProgram(scene->shader->prog);
    glUniform2f(scene->shader->glSceneScale, 2.0f / (float)dfbo.width, -2.0f / (float)dfbo.height);
    glUseProgram(0);
    glViewport(0, 0, width, height);
    drawFrame();
}

int main(int argc, char *argv[])
{
    window = initGLFWAndGLEW("OpenGL Application", 512, 512, &dfbo, key_callback);

    // AFramebuffer fbo = createAFramebuffer(dfbo.width / 4, dfbo.height / 4);
    glBindFramebuffer(GL_FRAMEBUFFER, dfbo.fbo);

    printf_s("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf_s("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf_s("Vendor: %s\n", glGetString(GL_VENDOR));

    AShader *sha = createShader("shader/basicVert.glsl", "shader/basicFrag.glsl");

    scene = createAScene();
    scene->shader = sha;

    addToAList(scene->basicShapes, createRectangleAA(0.0f, 0.0f, 362.0f, 128.0f));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    framebuffer_size_callback(window, 512, 512);

    selectedShape = scene->basicShapes->data[0];
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        drawFrame();
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