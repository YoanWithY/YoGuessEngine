#pragma once

typedef struct
{
    unsigned int max, size;
    void **data;
} AList;

AList createAList();

void addToList(AList *list, void *ptr);