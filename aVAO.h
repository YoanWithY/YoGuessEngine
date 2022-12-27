#pragma once

#include <glew.h>
#include "aArrayList.h"
#include "vec2.h"
#include "vec4.h"

typedef struct VAO
{
    // Number of indices.
    unsigned int numIndices;
    // The gl pointer to the VAO.
    GLuint glVAO;
    // The gl pointer to the IBO.
    GLuint glIBO;
    // The gl pointer to the PBO.
    GLuint glPBO;
    // The gl pointer to the VCBO.
    GLuint glVCBO;
    // The gl pointer to the SDFBO.
    GLuint glSDFBO;
    // The gl pointer to the ABO.
    GLuint glABO;
} VAO;

// Initilizes a VAO at the specified Pointer.
void initVAO(VAO *vao);

// Creates an Empty VAO.
VAO *createVAO();

// Creates a VAO from data.
VAO *createVAOFromData(unsigned int numIndices, unsigned int numVertices, unsigned int *ibo, vec2 *pbo, vec4 *vcbo, float *sdfbo, float *abo);

// Prints the VAO
void printVAO(VAO *vao);

/* Frees the memory on the OpenGL side by deleting the buffers. The C memory is also freed. After this call the VAO pointer is dangling.  */
void destroyVAO(VAO *vao);