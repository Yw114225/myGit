#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define elemtype int

typedef struct Node{
    struct Node* next;
    elemtype element;
}Node;


typedef struct Stack{
    struct Node* top;
    struct Node* bot;
    int size;
}Stack;

void StackCreate(Stack* stack);
void StackDestory(Stack* stack);
void StackPush(Stack* stack, elemtype val);
elemtype StackPop(Stack* stack);
elemtype StackTop(Stack* stack);
int StackSize(Stack* stack);
