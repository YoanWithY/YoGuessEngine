#pragma once
#include "aShader.h"
#include "aVAO.h"
#include "aList.h"

// An AScene contains the discription of a Scene in varius data types.
typedef struct AScene
{
    AShader *shader;
    AList *basicShapes;
} AScene;

// Creates a Scene.
AScene *createAScene();

// Frees all the allocates memory on the GL and C side as well as the scene object it self. After this call the AScene pointer is dangling.
void destroyScene(AScene *scene);