#include <stdlib.h>
#include "aList.h"

AList createAList()
{
    AList list = {16, 0, malloc(16 * sizeof(NULL))};
    return list;
}

void addToList(AList *list, void *ptr)
{
    if (list->capacity <= list->size)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(void *));
    }

    list->data[list->size] = ptr;
    list->size++;
}

void freeList(AList *list)
{
    free(list->data);
}