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
    createVertexArrayBufferAndAttribute(&vao->glCOVBO, 2, 1);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* Stores the given indices in the specified IBO. Note that the VAO the IBO belongs to should not be bound, because this function unbinds th GL_ELEMENT_ARRAY_BUFFER target which leads to the disconection of the IBO from the VAO which is assumend to be unwanted behavior. To avoid this situation this function unbinds the current VAO.*/
void storeIndexBufferInGLIBO(VAO *vao)
{
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->glIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vao->ibo.size * sizeof(unsigned int), vao->ibo.data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void storeFloatDataInGLVBO(GLuint vbo, AArrayList *list)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, list->size * list->elementSize, list->data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VAO createVAO()
{
    VAO vao = {
        createAArrayList(sizeof(unsigned int)),
        createAArrayList(sizeof(float) * 2),
        createAArrayList(sizeof(float) * 4),
        createAArrayList(sizeof(float)),
    };
    vaoInitGL(&vao);
    return vao;
}

// Creates a VAO from data.
VAO createVAOFromData(unsigned int numIndices, unsigned int numVertices, unsigned int ibo[], vec2 pbo[], vec4 vcbo[], float coverage[])
{
    VAO vao = createVAO();
    addArrayToArrayList(&vao.ibo, (void *)ibo, numIndices);
    addArrayToArrayList(&vao.pbo, (void *)pbo, numVertices);
    addArrayToArrayList(&vao.vcbo, (void *)vcbo, numVertices);
    addArrayToArrayList(&vao.coverage, (void *)coverage, numVertices);
    storeIndexBufferInGLIBO(&vao);
    storeFloatDataInGLVBO(vao.glPBO, &vao.pbo);
    storeFloatDataInGLVBO(vao.glVCBO, &vao.vcbo);
    storeFloatDataInGLVBO(vao.glCOVBO, &vao.coverage);
    return vao;
}

void printVAO(VAO *vao)
{
    printf("VAO:\nglVAO\tid:%d\nglIBO\tid:%d\nglPBO\tid:%d\nglVCBO\tid:%d\nglCOVBO\tid:%d\n", vao->glVAO, vao->glIBO, vao->glPBO, vao->glVCBO, vao->glCOVBO);
    printArrayList(&vao->ibo, 'd');
    printArrayList(&vao->pbo, 'f');
    printArrayList(&vao->vcbo, 'f');
    printArrayList(&vao->coverage, 'f');
}

void destroyVAO(VAO *vao)
{
    glDeleteBuffers(1, &vao->glIBO);
    glDeleteBuffers(1, &vao->glPBO);
    glDeleteBuffers(1, &vao->glVCBO);
    glDeleteBuffers(1, &vao->glCOVBO);
    freeArrayList(&vao->ibo);
    freeArrayList(&vao->pbo);
    freeArrayList(&vao->vcbo);
    freeArrayList(&vao->coverage);
}