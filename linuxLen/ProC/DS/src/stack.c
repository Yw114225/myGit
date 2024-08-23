#include "../inc/Stack.h"

void StackCreate(Stack* stack)
{
    stack->top  = NULL;
    stack->size = 0;
}

void StackDestory(Stack* stack)
{
    while(stack->top){
	Node* temp = stack->top;
	stack->top = stack->top->next;
	free(temp);
    }
    stack->size = 0;
}
void StackPush(Stack* stack, elemtype val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->element = val;
    newNode->next = stack->top;
    stack->top = newNode;
    ++stack->size;
}

elemtype StackPop(Stack* stack)
{
    if(!stack->top){
	printf("Stack is NULL\n");
	return -1;
    }
    elemtype ret = stack->top->element;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    --stack->size;
    return ret;
}

elemtype StackTop(Stack* stack){
    if(!stack->top){
	printf("Stack is NULL\n");
	return -1;
    }
    return stack->top->element;
}

int StackSize(Stack* stack)
{
    return stack->size;
}
 
