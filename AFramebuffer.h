#pragma once
#include <glew.h>

typedef struct AFramebuffer
{
    GLuint fbo;
    unsigned int width, height;
    GLuint colorRT;
} AFramebuffer;

// Constructor for an AFramebuffer.
AFramebuffer *createAFramebuffer(const unsigned int width, const unsigned int height);