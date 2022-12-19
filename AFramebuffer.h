#pragma once
#include <glew.h>

typedef struct
{
    GLuint fbo;
    unsigned int width, height;
    GLuint colorRT;
} AFramebuffer;

AFramebuffer createAFramebuffer(unsigned int width, unsigned int height);