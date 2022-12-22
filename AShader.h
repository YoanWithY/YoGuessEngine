#pragma once
#include <glew.h>

// AShader which contains the GL pointer to the linked program.
typedef struct AShader
{
    // The pointer to this shaders program
    GLuint prog;
} AShader;

// Initilizes an AShader at the specified pointer.
void initShader(AShader *shader, char *vertName, char *fragName);

/* Creates a AShader. */
AShader *createShader(char *vertName, char *fragName);

// Frees the underlying data and destroyes the object on the OpenGL side. After this call the shader pointer is dangling.
void destroyShader(AShader *const shader);