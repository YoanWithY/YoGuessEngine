#pragma once

// A list storing a variable number of elements. This conzept ist equivalent to a Vector in c++ or a ArrayList in Java.
typedef struct AList
{
    // Capacity in elements
    unsigned int capacity;
    // Size of list in elemts
    unsigned int size;
    // The pointer to the pointers.
    void **data;
} AList;

// Initilizes an AList at the specified pointer.
void initAList(AList *list);

// Constructor for an AList.
AList *createAList();

// Adds the specified element to the AList.
void addToAList(AList *list, void *ptr);

// Adds the specified array to the AList.
void addArrayToAList(AList *list, void *ptr, unsigned int numElements);

// Frees the underlying array and the AList it self. After this call the AList pointer is dangling.
void destroyAList(AList *list);