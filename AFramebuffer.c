#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include "aFramebuffer.h"

void initAFramebuffer(AFramebuffer *const fbo, const unsigned int width, const unsigned int height)
{
    fbo->width = width;
    fbo->height = height;
    glGenFramebuffers(1, &fbo->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo);

    glGenTextures(1, &fbo->colorRT);

    glBindTexture(GL_TEXTURE_2D, fbo->colorRT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

AFramebuffer *createAFramebuffer(const unsigned int width, const unsigned int height)
{
    AFramebuffer *fbo = malloc(sizeof(AFramebuffer));
    initAFramebuffer(fbo, width, height);

    return fbo;
}