#include <stdlib.h>
#include "aList.h"

AList createAList()
{
    AList list = {16, 0, malloc(16 * sizeof(NULL))};
    return list;
}

void addToList(AList *const list, void *const ptr)
{
    if (list->capacity <= list->size)
    {
        void **old = list->data;
        unsigned int oldMax = list->capacity;
        list->capacity *= 2;
        list->data = malloc(list->capacity * sizeof(NULL));

        for (int i = 0; i < oldMax; i++)
        {
            list->data[i] = old[i];
        }

        free(old);
    }

    list->data[list->size] = ptr;
    list->size++;
}