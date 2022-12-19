#pragma once
#include "AShader.h"
#include "VAO.h"
#include "AList.h"

typedef struct
{
    AShader shader;
    AList vaos;
} AScene;