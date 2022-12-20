#pragma once

typedef struct vec3
{
    float x, y, z;
} vec3;

vec3 vec3add(vec3 *a, vec3 *b);
vec3 vec3addf(vec3 *a, float f);