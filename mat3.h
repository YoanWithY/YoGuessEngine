#pragma once

#include "vec2.h"

// A squre matrix of size 3: [row, collumn]
typedef float mat3[3][3];

// Creates a mat3.
mat3 *createMat3();

void setMat3Identity(mat3 *mat);

void makeRotatationTranslationTransformation(mat3 mat, float rotation, vec2 *tranlation);

void printMat3(mat3 mat);

void printMat3P(float mat[9]);

void destroyMat3(mat3 *mat);