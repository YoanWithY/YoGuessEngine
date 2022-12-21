#pragma once
#include <glew.h>

typedef struct AShader
{
    // The pointer to this shaders program
    GLuint prog;
} AShader;

AShader createShader(char vertName[], char fragName[]);

void destroyShader(AShader *shader);