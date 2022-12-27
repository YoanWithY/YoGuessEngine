#include <stdlib.h>
#include <stdio.h>
#include <glew.h>
#include <math.h>
#include "basicShape.h"
#include "vec2.h"

void initShape(BasicShape *shape, void (*genBasicShape)(VAO *, float *))
{
    shape->translation = createVec2(0.0f, 0.0f);
    shape->rotation = 0.0f;
}
// stores the required vertex data in the respective pbo. @param d {x, y, width, height}
static void genRect(VAO *vao, float d[])
{
    glBindBuffer(GL_ARRAY_BUFFER, vao->glPBO);
    float pbo[] = {d[0], d[1], d[0], d[1] + d[3], d[0] + d[2], d[1] + d[3], d[0] + d[2], d[1]};
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pbo), pbo);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BasicShape *createRectangle(float x, float y, float width, float height)
{
    BasicShape *rect = malloc(sizeof(BasicShape));
    initShape(rect, genRect);

    unsigned int ibo[] = {0, 1, 2, 0, 2, 3};
    vec2 pbo[] = {{x, y}, {x, y + height}, {x + width, y + height}, {x + width, y}};
    vec4 vcbo[] = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}};
    float sdfbo[] = {-1.0f, -1.0f, -1.0f, -1.0f};
    float abo[] = {0, 0, 0, 0};

    rect->vao = createVAOFromData(6, 4, ibo, pbo, vcbo, sdfbo, abo);

    return rect;
}

BasicShape *createRectangleAA(float x, float y, float width, float height)
{
    BasicShape *rect = malloc(sizeof(BasicShape));
    initShape(rect, genRect);
    float d = (float)(sqrt(2) / 2.0);

    vec2 ul0 = {x - d, y - d};
    vec2 ul1 = {x + d, y + d};
    vec2 ur0 = {x + width + d, y - d};
    vec2 ur1 = {x + width - d, y + d};
    vec2 lr0 = {x + width + d, y + height + d};
    vec2 lr1 = {x + width - d, y + height - d};
    vec2 ll0 = {x - d, y + height + d};
    vec2 ll1 = {x + d, y + height - d};

    unsigned int ibo[] = {0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7, 8, 9, 10, 10, 9, 11, 12, 13, 14, 14, 13, 15, 1, 13, 9, 1, 9, 5};
    vec2 pbo[] = {ul0, ul1, ur0, ur1, ur0, ur1, lr0, lr1, lr0, lr1, ll0, ll1, ll0, ll1, ul0, ul1};
    float abo[] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1};

    vec4 vcbo[] = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f}};
    float sdfbo[] = {d, -d, d, -d, d, -d, d, -d, d, -d, d, -d, d, -d, d, -d};

    rect->vao = createVAOFromData(30, 16, ibo, pbo, vcbo, sdfbo, abo);
    return rect;
}

void destroyBasicShape(BasicShape *shape)
{
    destroyVAO(shape->vao);
    destroyVec2(shape->translation);
    free(shape);
}