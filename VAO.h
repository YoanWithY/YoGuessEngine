#pragma once

typedef struct
{
    unsigned int *ibo;
    float *pbo;
    float *vcbo;
    float *coverage;
    // the number of indiced
    unsigned int numIndices;
    // the number of vertices
    unsigned int numVertices;
    // indicates if the bufferes were allocated with malloc (1) or not (0);
    unsigned char isMalloceted;
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

// Creates an Empty VAO by allocating the requred space using malloc, than reflects that data to OpenGL.
VAO cretateVAO(unsigned int numIndices, unsigned int numVertices);

// Creates a VAO data structure and initilizes its content with the given arrays, than reflects the date to OpenGL.
VAO cretateVAOByData(unsigned int numIndices, unsigned int numVertices, unsigned int *ibo, float *pbo, float *vcbo, float *coverage);

/* Frees the memory on the OpenGL side by deleting the buffers. If the VAO was dynamicaly allocated using malloc,
the c memory will also be freed. After this call the handed VAO has no use anymore. */
void destroyVAO(VAO *vao);