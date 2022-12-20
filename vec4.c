#include "vec4.h"

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