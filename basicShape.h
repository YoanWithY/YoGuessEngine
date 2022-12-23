#pragma once
#include "vec2.h"
#include "aVAO.h"

typedef struct BasicShape
{
    vec2 *translation;
    float rotation;
    void (*genBasicShape)(VAO *, float *);
    VAO *vao;
} BasicShape;

BasicShape *createShape();

BasicShape *createRectangle(float x, float y, float width, float height);

BasicShape *createRectangleAA(float x, float y, float width, float height);

void destroyBasicShape(BasicShape *shape);