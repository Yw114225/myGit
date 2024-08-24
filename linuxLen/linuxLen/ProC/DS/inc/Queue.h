#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define elemtype int

typedef struct Node
{
    struct Node* next;
    elemtype element;
}Node;

typedef struct Queue
{
    struct Node* front;
    struct Node* rear;
    int   size;
}Queue;

void QueueCreate(Queue* queue);
void QueueDestory(Queue* queue);
void QueuePush(Queue* queue, elemtype val);
elemtype QueuePop(Queue* queue);
elemtype QueueTop(Queue* queue);
int QueueSize(Queue* queue);

