#pragma once

typedef struct
{
    // The pointer to this shaders program
    GLuint prog;
} AShader;

AShader createShader(char vertName[], char fragName[]);