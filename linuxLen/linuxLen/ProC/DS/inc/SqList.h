#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define elemtype int

typedef struct {
    elemtype* element;
    int    size;
    int    capacity;
}SequentialList;

void SqInit(SequentialList* Sq, int capacity);

void SqDestory(SequentialList* Sq);

void SqPrint(SequentialList* Sq);

int SqInsert(SequentialList* Sq, int pos, elemtype val);

void SqDelete(SequentialList* Sq, int pos);

void SqSet(SequentialList* Sq, int pos, elemtype val);

void SqIndex(SequentialList* Sq, elemtype val);
