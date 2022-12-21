#include <stdlib.h>
#include "aScene.h"

void destroyScene(AScene *scene)
{
    destroyShader(&scene->shader);

    for (unsigned int i = 0; i < scene->vaos.size; i++)
    {
        destroyVAO((VAO *)scene->vaos.data[i]);
    }

    freeList(&scene->vaos);
}