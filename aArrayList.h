#pragma once

// A list storing a variable number of elements. This conzept ist equivalent to a Vector in c++ or a ArrayList in Java.
typedef struct AArrayList
{
    // Capacity in elements
    unsigned int capacity;
    // Size of list in elemts
    unsigned int size;
    // The size of one element of the list.
    const unsigned int sizeOfElement;
    // The pointer to the actual data.
    void *data;
} AArrayList;

// Initilizes an ArrayList at the specified pointer.
void initAArrayList(AArrayList *list, unsigned int sizeOfElement);

// Constructor for an ArrayList.
AArrayList *createAArrayList(unsigned int sizeOfElement);

// Adds the specified element to the ArrayList.
void addToArrayAArrayList(AArrayList *list, void *ptr);

// Adds the specified array to the ArrayList.
void addArrayToAArrayList(AArrayList *list, void *ptr, unsigned int numElements);

// Print the array. The format of is determined by c. @param c The format.
void printArrayList(AArrayList *list, char c);

// Frees the underlying array and the list it self. After this call the list pointer is dangling.
void destroyArrayList(AArrayList *list);