#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aArrayList.h"

AArrayList createAArrayList(unsigned int elementSize)
{
    AArrayList list = {1, 0, elementSize, malloc(16 * elementSize)};
    return list;
}

// Adds the specified element to the ArrayList.
void addToArrayList(AArrayList *list, void *ptr)
{
    if (list->capacity <= list->size)
    {
        void *old = list->data;
        list->capacity *= 2;
        list->data = malloc(list->capacity * sizeof(list->elementSize));

        memcpy(list->data, old, list->size * list->elementSize);

        free(old);
    }

    char *cast = (char *)list->data;
    memcpy(cast, ptr, list->elementSize);
    list->size++;
}

// Adds the specified array to the ArrayList.
void addArrayToArrayList(AArrayList *list, void *ptr, unsigned int numElements)
{
    if (list->capacity <= list->size + numElements)
    {
        void *old = list->data;
        list->capacity = list->size + numElements + 4;
        list->data = malloc(list->capacity * sizeof(list->elementSize));

        memcpy(list->data, old, list->size * list->elementSize);

        free(old);
    }

    char *cast = (char *)list->data;
    memcpy(cast + (list->size * list->elementSize), ptr, numElements * list->elementSize);
    list->size += numElements;
}

void printArrayList(AArrayList *list, const char c)
{
    printf("ArrayList:\n\tsize:\t\t%u\n\telement size:\t%u\n\tcapacity:\t%u\n\t[", list->size, list->elementSize, list->capacity);

    switch (c)
    {
    case 'd':
    {
        int *data = (int *)list->data;
        for (unsigned int i = 0; i < list->size * (list->elementSize / sizeof(int) - 1); i++)
        {
            printf("%d, ", data[i]);
        }
        printf("%d", data[list->size]);
        break;
    }
    case 'f':
    {
        float *data = (float *)list->data;
        for (unsigned int i = 0; i < list->size * (list->elementSize / sizeof(float) - 1); i++)
        {
            printf("%f, ", data[i]);
        }
        printf("%f", data[list->size]);
        break;
    }

    default:
        break;
    }

    printf("]\n");
}

void freeArrayList(AArrayList *list)
{
    free(list->data);
}