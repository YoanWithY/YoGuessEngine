#include <stdlib.h>
#include <stdio.h>
#include <glew.h>
#include "aArrayList.h"
#include "aVAO.h"
#include "vec2.h"
#include "vec4.h"

static void createElementArrayBuffer(GLuint *IBO)
{
    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
}

static void createVertexArrayBufferAndAttribute(GLuint *VBO, unsigned char attribNum, unsigned char size)
{
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glVertexAttribPointer(attribNum, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void vaoInitGL(VAO *vao)
{
    glGenVertexArrays(1, &(vao->glVAO));
    glBindVertexArray(vao->glVAO);
    createElementArrayBuffer(&(vao->glIBO));
    createVertexArrayBufferAndAttribute(&vao->glPBO, 0, 2);
    createVertexArrayBufferAndAttribute(&vao->glVCBO, 1, 4);
    createVertexArrayBufferAndAttribute(&vao->glSDFBO, 2, 1);
    createVertexArrayBufferAndAttribute(&vao->glABO, 3, 1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Stores the given indices in the specified IBO. Note that the VAO the IBO belongs to should not be bound, because this function unbinds th GL_ELEMENT_ARRAY_BUFFER target which leads to the disconection of the IBO from the VAO which is assumend to be unwanted behavior. To avoid this situation this function unbinds the current VAO.*/
void storeIndexBufferInGLIBO(VAO *vao, unsigned int numIndices, unsigned int *ibo)
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->glIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), ibo, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void storeFloatDataInGLVBO(GLuint vbo, unsigned int numFloats, float *list)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), list, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VAO *createVAO()
{
    VAO *vao = malloc(sizeof(VAO));
    vaoInitGL(vao);
    return vao;
}

VAO *createVAOFromData(unsigned int numIndices, unsigned int numVertices, unsigned int *ibo, vec2 *pbo, vec4 *vcbo, float *sdfbo, float *abo)
{
    VAO *vao = createVAO();
    vao->numIndices = numIndices;
    storeIndexBufferInGLIBO(vao, numIndices, ibo);
    storeFloatDataInGLVBO(vao->glPBO, numVertices * 2, (float *)pbo);
    storeFloatDataInGLVBO(vao->glVCBO, numVertices * 4, (float *)vcbo);
    storeFloatDataInGLVBO(vao->glSDFBO, numVertices, sdfbo);
    storeFloatDataInGLVBO(vao->glABO, numVertices, abo);
    return vao;
}

void printVAO(VAO *vao)
{
    printf("VAO:\nglVAO\tid:%d\nglIBO\tid:%d\nglPBO\tid:%d\nglVCBO\tid:%d\nglCOVBO\tid:%d\n", vao->glVAO, vao->glIBO, vao->glPBO, vao->glVCBO, vao->glSDFBO);
}

void destroyVAO(VAO *vao)
{
    glDeleteBuffers(1, &vao->glIBO);
    glDeleteBuffers(1, &vao->glPBO);
    glDeleteBuffers(1, &vao->glVCBO);
    glDeleteBuffers(1, &vao->glSDFBO);
    free(vao);
}