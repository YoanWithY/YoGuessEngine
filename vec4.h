#pragma once

typedef struct vec4
{
    float x, y, z, w;
} vec4;

vec4 vec4add(vec4 *a, vec4 *b);
vec4 vec4addf(vec4 *a, float f);