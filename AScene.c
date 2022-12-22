#include <stdlib.h>
#include <stdio.h>
#include "aVAO.h"
#include "aScene.h"
#include "aList.h"

void initAScene(AScene *scene)
{
    scene->vaos = createAList(sizeof(VAO));
}

AScene *createAScene()
{
    AScene *scene = malloc(sizeof(AScene));
    initAScene(scene);
    return scene;
};

void destroyScene(AScene *scene)
{
    destroyShader(scene->shader);

    for (unsigned int i = 0; i < scene->vaos->size; i++)
    {
        destroyVAO((VAO *)scene->vaos->data[i]);
    }
    destroyAList(scene->vaos);

    free(scene);
}