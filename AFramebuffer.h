#pragma once
#include <glew.h>

typedef struct AFramebuffer
{
    GLuint fbo;
    unsigned int width, height;
    GLuint colorRT;
} AFramebuffer;

// Initilizes a AFramebuffer at the specified pointer.
void initAFramebuffer(AFramebuffer *const fbo, const unsigned int width, const unsigned int height);

// Constructor for an AFramebuffer.
AFramebuffer *createAFramebuffer(const unsigned int width, const unsigned int height);