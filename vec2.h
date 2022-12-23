#pragma once

typedef struct vec2
{
    float x, y;
} vec2;

vec2 *createVec2(float x, float y);

vec2 vec2add(vec2 *a, vec2 *b);
vec2 vec2addf(vec2 *a, float b);

void destroyVec2(vec2 *vec);