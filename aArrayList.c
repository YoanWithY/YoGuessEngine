#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aArrayList.h"

void initAArrayList(AArrayList *list, unsigned int sizeOfElement)
{
    AArrayList l = {8, 0, sizeOfElement, malloc(8 * sizeOfElement)};
    memcpy(list, &l, sizeof(AArrayList));
}

AArrayList *createAArrayList(unsigned int sizeOfElement)
{

    AArrayList *list = malloc(sizeof(AArrayList));
    initAArrayList(list, sizeOfElement);
    return list;
}

void addToArrayList(AArrayList *list, void *ptr)
{
    if (list->capacity <= list->size)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->sizeOfElement);
    }

    char *cast = (char *)list->data;
    memcpy(cast, ptr, list->sizeOfElement);
    list->size++;
}

void addArrayToArrayList(AArrayList *list, void *ptr, unsigned int numElements)
{
    if (list->capacity <= list->size + numElements)
    {
        list->capacity = list->size + numElements + 4;
        list->data = realloc(list->data, list->capacity * list->sizeOfElement);
    }

    char *cast = (char *)list->data;
    memcpy(cast + (list->size * list->sizeOfElement), ptr, numElements * list->sizeOfElement);
    list->size += numElements;
}

void printArrayList(AArrayList *list, char c)
{
    printf("ArrayList:\n\tsize:\t\t%u\n\telement size:\t%u\n\tcapacity:\t%u\n\t[", list->size, list->sizeOfElement, list->capacity);

    switch (c)
    {
    case 'd':
    {
        int *data = (int *)list->data;
        for (unsigned int i = 0; i < list->size * (list->sizeOfElement / sizeof(int)) - 1; i++)
        {
            printf("%d, ", data[i]);
        }
        printf("%d", data[list->size - 1]);
        break;
    }
    case 'f':
    {
        float *data = (float *)list->data;
        for (unsigned int i = 0; i < list->size * (list->sizeOfElement / sizeof(float)) - 1; i++)
        {
            printf("%f, ", data[i]);
        }
        printf("%f", data[list->size - 1]);
        break;
    }

    default:
        break;
    }

    printf("]\n");
}

void destroyArrayList(AArrayList *list)
{
    free(list->data);
    free(list);
}