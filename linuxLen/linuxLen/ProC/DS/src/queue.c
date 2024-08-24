#include "../inc/Queue.h"

void QueueCreate(Queue* queue)
{
    queue->front = queue->rear  = NULL;
    queue->size   = 0;
}

void QueueDestory(Queue* queue)
{
    while(queue->front != NULL){
	Node* temp = queue->front;
	queue->front = queue->front->next;
	free(temp);
    }
    queue->rear = NULL;
    queue->size = 0;
}

void QueuePush(Queue* queue, elemtype val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->element = val;
    newNode->next = NULL;
    if(!queue->rear){
	queue->front = newNode;
	queue->rear  = newNode;
    }
    else{
	queue->rear->next = newNode;
	queue->rear = newNode;
    }
    ++queue->size;
}

elemtype QueuePop(Queue* queue)
{
    if(!queue->front){
	printf("The Queue is NULL\n");
	return -1;
    }
    elemtype ret = queue->front->element;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    --queue->size;
    return ret;
}

elemtype QueueTop(Queue* queue)
{
    if(!queue->front){
	printf("The Queue is NULL\n");
	return -1;
    }
    return queue->front->element;
}

int QueueSize(Queue* queue)
{
    return queue->size;
}
