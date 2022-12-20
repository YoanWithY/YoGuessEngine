#pragma once

typedef struct
{
    unsigned int capacity, size;
    void **data;
} AList;

AList createAList();

void addToList(AList *list, void *ptr);