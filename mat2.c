#include <stdlib.h>
#include "mat2.h"

mat2 *createMat2()
{
    mat2 *mat = malloc(sizeof(mat2));
    return mat;
}

void setMat2Identity(mat2 *mat)
{
    *mat[0][0] = 1;
    *mat[0][1] = 0;
    *mat[1][0] = 0;
    *mat[1][1] = 1;
}