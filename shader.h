#pragma once

typedef struct
{
    // The pointer to this shaders program
    GLuint prog;
} shader;

shader createShader(char vertName[], char fragName[]);