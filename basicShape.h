#pragma once
#include "vec2.h"
#include "aVAO.h"

typedef struct BasicShape
{
    vec2 translation;
    float rotation;
    void (*genBasicShape)(VAO *, float *);
    VAO *vao;
} BasicShape;

// Initilzases a BasicShape with exeption of the vao.
void initShape(BasicShape *shape, void (*genBasicShape)(VAO *, float *));

BasicShape *createShape();

BasicShape *createRectangle(float x, float y, float width, float height);

void destroyBasicShape(BasicShape *shape);