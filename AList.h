#pragma once

typedef struct AList
{
    unsigned int capacity, size;
    void **data;
} AList;

AList createAList();

void addToList(AList *list, void *ptr);

// Frees the data allocated for this list. @note The list only consists of pointers. The memory they point to will be left unchanged.
void freeList(AList *list);