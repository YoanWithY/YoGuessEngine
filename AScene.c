#include <stdlib.h>
#include <stdio.h>
#include "basicShape.h"
#include "aScene.h"
#include "aList.h"

void initAScene(AScene *scene)
{
    scene->basicShapes = createAList(sizeof(BasicShape));
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

    for (unsigned int i = 0; i < scene->basicShapes->size; i++)
    {
        destroyBasicShape((BasicShape *)scene->basicShapes->data[i]);
    }
    destroyAList(scene->basicShapes);

    free(scene);
}