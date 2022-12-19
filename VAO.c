#include <stdlib.h>
#include <stdio.h>
#include <glew.h>
#include "VAO.h"

static void storeIndexBufferInGLIBO(unsigned int numIndices, unsigned int data[], GLuint *IBO)
{
    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

static void storeFloatDataInGLVBO(unsigned char attribNum, unsigned int size, unsigned int numVertices, float data[], GLuint *VBO)
{
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, numVertices * size * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribNum, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attribNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void vaoInitGL(VAO *vao)
{
    glGenVertexArrays(1, &(vao->glVAO));
    glBindVertexArray(vao->glVAO);
    storeIndexBufferInGLIBO(vao->numIndices, vao->ibo, &(vao->glIBO));
    storeFloatDataInGLVBO(0, 2, vao->numVertices, vao->pbo, &(vao->glPBO));
    storeFloatDataInGLVBO(1, 4, vao->numVertices, vao->vcbo, &(vao->glCOVBO));
    storeFloatDataInGLVBO(2, 1, vao->numVertices, vao->coverage, &(vao->glCOVBO));
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VAO cretateVAO(unsigned int numIndices, unsigned int numVertices)
{
    VAO vao = {malloc(numIndices * sizeof(unsigned int)),
               malloc(numVertices * sizeof(float) * 2),
               malloc(numVertices * sizeof(float) * 4),
               malloc(numVertices * sizeof(float)),
               numIndices,
               numVertices,
               (unsigned char)1};
    vaoInitGL(&vao);
    return vao;
}

VAO cretateVAOByData(unsigned int numIndices, unsigned int numVertices, unsigned int ibo[], float pbo[], float vcbo[], float coverage[])
{
    VAO vao = {ibo, pbo, vcbo, coverage, numIndices, numVertices, (unsigned char)0};
    vaoInitGL(&vao);
    return vao;
}

void destroyVAO(VAO *vao)
{
    glDeleteBuffers(1, &vao->glIBO);
    glDeleteBuffers(1, &vao->glPBO);
    glDeleteBuffers(1, &vao->glVCBO);
    glDeleteBuffers(1, &vao->glCOVBO);

    if (vao->isMalloceted)
    {
        free(vao->ibo);
        free(vao->pbo);
        free(vao->vcbo);
        free(vao->coverage);
    }
}