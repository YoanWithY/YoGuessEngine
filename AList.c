#include <stdlib.h>
#include "AList.h"

AList createAList()
{
    AList list = {16, 0, malloc(16 * sizeof(NULL))};
    return list;
}

void addToList(AList *list, void *ptr)
{
    if (list->max <= list->size)
    {
        void **old = list->data;
        unsigned int oldMax = list->max;
        list->max *= 2;
        list->data = malloc(list->max * sizeof(NULL));

        for (int i = 0; i < oldMax; i++)
        {
            list->data[i] = old[i];
        }

        free(old);
    }

    list->data[list->size] = ptr;
    list->size++;
}