#include <stdlib.h>
#include "vec4.h"

vec4 *createVec4(float x, float y, float z, float w)
{
    vec4 *vec = malloc(sizeof(float) * 4);
    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->w = w;
    return vec;
}

vec4 vec4add(vec4 *a, vec4 *b)
{
    vec4 r = {a->x + b->x, a->x + b->y, a->z + b->z};
    return r;
}

vec4 vec4addf(vec4 *a, float f)
{
    vec4 r = {a->x + f, a->x + f, a->z + f};
    return r;
}

void destroyVec4(vec4 *vec)
{
    free(vec);
}