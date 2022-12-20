#pragma once
#include "aShader.h"
#include "aVAO.h"
#include "aList.h"

typedef struct
{
    AShader shader;
    AList vaos;
} AScene;