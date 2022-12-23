#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mat3.h"

mat3 *createMat3()
{
    mat3 *mat = malloc(sizeof(mat3));
    return mat;
}

void setMat3Identity(mat3 *mat)
{
    *mat[0][0] = *mat[1][1] = *mat[2][2] = 1;
    *mat[0][1] = *mat[0][2] = *mat[1][0] = *mat[1][2] = *mat[2][0] = *mat[2][1] = 0;
}

void makeRotatationTranslationTransformation(mat3 mat, float rotation, vec2 *translation)
{
    mat[0][0] = cos(rotation);
    mat[1][0] = sin(rotation);
    mat[2][0] = 0;

    mat[0][1] = -mat[1][0];
    mat[1][1] = mat[0][0];
    mat[2][1] = 0;

    mat[0][2] = translation->x;
    mat[1][2] = translation->y;
    mat[2][2] = 1;
};

void printMat3(mat3 mat)
{
    printf("mat3:\n");
    printf("%f %f %f \n", mat[0][0], mat[0][1], mat[0][2]);
    printf("%f %f %f \n", mat[1][0], mat[1][1], mat[1][2]);
    printf("%f %f %f \n", mat[2][0], mat[2][1], mat[2][2]);
}

void printMat3P(float mat[9])
{
    printf("%f %f %f \n", mat[0], mat[1], mat[2]);
    printf("%f %f %f \n", mat[3], mat[4], mat[5]);
    printf("%f %f %f \n", mat[6], mat[7], mat[8]);
}

void destroyMat3(mat3 *mat)
{
    free(mat);
}