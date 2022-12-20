#include "vec3.h"

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