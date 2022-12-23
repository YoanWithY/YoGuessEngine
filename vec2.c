#include <stdlib.h>
#include "vec2.h"

vec2 *createVec2(float x, float y)
{
    vec2 *vec = malloc(sizeof(float) * 2);
    vec->x = x;
    vec->y = y;
    return vec;
}

vec2 vec2add(vec2 *a, vec2 *b)
{
    vec2 r = {a->x + b->x, a->x + b->y};
    return r;
}

vec2 vec2addf(vec2 *a, float f)
{
    vec2 r = {a->x + f, a->x + f};
    return r;
}

void destroyVec2(vec2 *vec)
{
    free(vec);
}