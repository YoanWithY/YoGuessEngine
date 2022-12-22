#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aList.h"

void initAList(AList *list)
{
    list->size = 0;
    list->capacity = 8;
    list->data = malloc(list->capacity * sizeof(NULL));
}

AList *createAList()
{
    AList *list = malloc(sizeof(AList));
    initAList(list);
    return list;
}

void addToAList(AList *list, void *ptr)
{
    if (list->capacity <= list->size)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(NULL));
    }

    list->data[list->size] = ptr;
    list->size++;
}

void addArrayToAList(AList *list, void **ptr, unsigned int numElements)
{
    if (list->capacity <= list->size + numElements)
    {
        list->capacity = list->size + numElements + 4;
        list->data = realloc(list->data, list->capacity * sizeof(NULL));
    }

    for (unsigned int i = 0; i < numElements; i++)
    {
        list->data[list->size + i] = ptr[i];
    }

    list->size += numElements;
}

void destroyAList(AList *list)
{
    free(list->data);
    free(list);
}