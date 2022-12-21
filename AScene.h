#pragma once
#include "aShader.h"
#include "aVAO.h"
#include "aList.h"

typedef struct AScene
{
    AShader shader;
    AList vaos;
} AScene;

void destroyScene(AScene *scene);