#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include "aFramebuffer.h"

AFramebuffer *createAFramebuffer(const unsigned int width, const unsigned int height)
{
    AFramebuffer *fbo = malloc(sizeof(AFramebuffer));

    fbo->width = width;
    fbo->height = height;
    glGenFramebuffers(1, &fbo->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo);

    glGenTextures(1, &fbo->colorRT);

    glBindTexture(GL_TEXTURE_2D, fbo->colorRT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return fbo;
}