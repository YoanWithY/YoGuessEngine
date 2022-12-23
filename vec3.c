#include <stdlib.h>
#include "vec3.h"

vec3 *createVec3(float x, float y, float z)
{
    vec3 *vec = malloc(sizeof(float) * 3);
    vec->x = x;
    vec->y = y;
    vec->z = z;
    return vec;
}

vec3 vec3add(vec3 *a, vec3 *b)
{
    vec3 r = {a->x + b->x, a->x + b->y, a->z + b->z};
    return r;
}

vec3 vec3addf(vec3 *a, float f)
{
    vec3 r = {a->x + f, a->x + f, a->z + f};
    return r;
}

void destroyVec3(vec3 *vec)
{
    free(vec);
}