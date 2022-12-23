#include <stdlib.h>
#include <stdio.h>
#include <glew.h>
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
    float covbo[] = {1.0f, 1.0f, 1.0f, 1.0f};

    rect->vao = createVAOFromData(6, 4, ibo, pbo, vcbo, covbo);

    return rect;
}

BasicShape *createRectangleAA(float x, float y, float width, float height)
{
    BasicShape *rect = malloc(sizeof(BasicShape));
    initShape(rect, genRect);

    unsigned int ibo[] = {0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 7, 1, 1, 7, 3, 3, 7, 5};
    vec2 pbo[] = {
        {x - 0.5f, y - 0.5f},
        {x + 0.5f, y + 0.5f},
        {x + width + 0.5f, y - 0.5f},
        {x + width - 0.5f, y + 0.5f},
        {x + width + 0.5f, y + height + 0.5f},
        {x + width - 0.5f, y + height - 0.5f},
        {x - 0.5f, y + height + 0.5f},
        {x + 0.5f, y + height - 0.5f}};

    vec4 vcbo[] = {{0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f},
                   {0.0f, 0.0f, 0.0f, 1.0f}};
    float covbo[] = {0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f};

    rect->vao = createVAOFromData(30, 8, ibo, pbo, vcbo, covbo);
    return rect;
}

void destroyBasicShape(BasicShape *shape)
{
    destroyVAO(shape->vao);
    destroyVec2(shape->translation);
    free(shape);
}