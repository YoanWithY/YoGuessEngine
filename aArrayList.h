#pragma once

typedef struct
{
    // Capacity in elements
    unsigned int capacity;
    // Size of list in elemts
    unsigned int size;
    const unsigned int elementSize;
    void *data;
} AArrayList;

AArrayList createAArrayList(unsigned int elementSize);

void addToArrayList(AArrayList *list, void *ptr);
void addArrayToArrayList(AArrayList *list, void *ptr, unsigned int numElements);
void printArrayList(AArrayList *list, const char c);
void freeArrayList(AArrayList *list);