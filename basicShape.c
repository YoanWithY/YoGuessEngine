#include <stdlib.h>
#include <glew.h>
#include "basicShape.h"

void initShape(BasicShape *shape, void (*genBasicShape)(VAO *, float *))
{
    shape->translation.x = 0.0f;
    shape->translation.y = 0.0f;
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

void destroyBasicShape(BasicShape *shape)
{
    destroyVAO(shape->vao);
    free(shape);
}