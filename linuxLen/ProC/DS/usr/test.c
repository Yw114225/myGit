#include "../inc/SqList.h"
//#include "../inc/Queue.h"
#include "../inc/Stack.h"

int main(int argc, char* argv[])
{
   /*SequentialList Sq;
    SqInit(&Sq, 4);
    //SqInit(&Sq, 3);
    //SqPrint(&Sq);
    SqInsert(&Sq, 0, 0);
    SqInsert(&Sq, 1, 1);
    SqInsert(&Sq, 2, 2);
    SqInsert(&Sq, 3, 3);
    SqInsert(&Sq, 4, 4);
    SqPrint(&Sq);
    SqIndex(&Sq, 3);
    SqDelete(&Sq, 0);
    SqIndex(&Sq, 0);*/
   /* Queue q1;
    QueueCreate(&q1);
    QueuePush(&q1, 0);
    QueuePush(&q1, 1);
    QueuePush(&q1, 2);
    QueuePush(&q1, 3);
    QueuePush(&q1, 4);
    printf("q1's front is %d\n", QueueTop(&q1));
    QueuePop(&q1);
    printf("q1's front is %d\n", QueueTop(&q1));
    QueueDestory(&q1);
    printf("q1's front is %d\n", QueueTop(&q1));*/
    Stack s1;
    StackCreate(&s1);
    for(int i = 0; i < 5; ++i){
	StackPush(&s1, i);
    }
    printf("s1 size = %d\n", StackSize(&s1));
    printf("s1's top is %d\n", StackTop(&s1));
    StackPop(&s1);
    printf("s1's top is %d\n", StackTop(&s1));
    StackDestory(&s1);
    printf("s1's top is %d\n", StackTop(&s1));
    return 0;
}
