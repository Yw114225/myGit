#include "../inc/SqList.h"

void SqInit(SequentialList* Sq, int capacity)
{
    /*if((Sq->element = (elemtype*)malloc(sizeof(elemtype) * capacity)) == NULL)
    {
	printf("Init failed\n");
	return ;
    }*/
    puts("");
    Sq->element = (elemtype*)malloc(sizeof(elemtype) * capacity);
    Sq->size = 0;
    Sq->capacity = capacity;
    //puts("");
}

void SqDestory(SequentialList* Sq)
{
    Sq->size = 0;
    Sq->capacity = 0;
    free(Sq->element);
    Sq->element = NULL;
}

void SqPrint(SequentialList* Sq)
{
    printf("SQ:");
    for(int i = 0; i < Sq->size; ++i)
	printf("%d ", Sq->element[i]);
    puts("");
}

int SqInsert(SequentialList* Sq, int pos, elemtype val)
{
    //printf("1 ");
    if(pos < 0 || pos > Sq->size){
	printf("Insert failed\n");
	return -1;
    }
    if(Sq->size + 1 > Sq->capacity){
	elemtype* Newelem = (elemtype*)realloc(Sq->element, sizeof(elemtype)*Sq->capacity*2);
	Sq->element = Newelem;
    }
    //printf("0 ");
    Sq->element[pos] = val;
    //printf("2\n");
    ++Sq->size;
    return 1;
}

void SqDelete(SequentialList* Sq, int pos)
{
    for(int i = pos; i < Sq->size - 1; ++i){
	Sq->element[i] = Sq->element[i+1];
    }
    --Sq->size;
}

void SqSet(SequentialList* Sq, int pos, elemtype val)
{
    Sq->element[pos] = val;
}

void SqIndex(SequentialList* Sq, elemtype val)
{
    for(int i = 0; i < Sq->size; ++i){
	if(Sq->element[i] == val){
	    printf("found %d in Sq[%d]\n", val, i);
	    return ;
	}
    }
    printf("not found %d\n", val);
}
