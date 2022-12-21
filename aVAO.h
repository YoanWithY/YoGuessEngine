#pragma once

#include <glew.h>
#include "aArrayList.h"
#include "vec2.h"
#include "vec4.h"

typedef struct VAO
{
    // A list containing indices -> 1 unsigned int per index.
    AArrayList ibo;
    // A list containing position data -> 1 vec2(x, y) per vertex.
    AArrayList pbo;
    // A list containg vertex color data -> 1 vec4(r, g, b, a) per vertex.
    AArrayList vcbo;
    // Alist containg coverage data -> 1 float per vertex.
    AArrayList coverage;
    // The gl pointer to the VAO.
    GLuint glVAO;
    // The gl pointer to the IBO.
    GLuint glIBO;
    // The gl pointer to the PBO.
    GLuint glPBO;
    // The gl pointer to the VCBO.
    GLuint glVCBO;
    // The gl pointer to the COVBO.
    GLuint glCOVBO;
} VAO;

// Creates an Empty VAO.
VAO createVAO();

// Creates a VAO from data.
VAO createVAOFromData(unsigned int numIndices, unsigned int numVertices, unsigned int ibo[], vec2 pbo[], vec4 vcbo[], float coverage[]);

// Prints the VAO
void printVAO(VAO *vao);

/* Frees the memory on the OpenGL side by deleting the buffers. The C memory will also be freed. After this call the handed VAO has no use anymore. */
void destroyVAO(VAO *vao);