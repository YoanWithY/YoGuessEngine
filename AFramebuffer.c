#include <glew.h>
#include "AFramebuffer.h"

AFramebuffer createAFramebuffer(unsigned int width, unsigned int height)
{
    AFramebuffer fbo = {0, width, height, 0};
    glGenFramebuffers(1, &fbo.fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.fbo);

    glGenTextures(1, &fbo.colorRT);

    glBindTexture(GL_TEXTURE_2D, fbo.colorRT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return fbo;
}