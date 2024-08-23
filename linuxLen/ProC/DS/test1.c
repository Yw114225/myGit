#include <stdio.h>
#include <stdlib.h>

#define elemtype int
/* 实现顺序表的创建 销毁 扩容 增删改查*/
typedef struct{
    elemtype* element;
    size_t size;
    size_t capacity;
}ConsequentialList;

//创建顺序表
void ConsequentialListCreate(ConsequentialList* list, size_t capacity){
    list->element = (elemtype*)malloc(sizeof(elemtype) * capacity);
    list->capacity = capacity;
    list->size = 0;
}
//销毁顺序表
void ConsequentialListDestory(ConsequentialList* list){
    if(list->element){
        free(list->element);
        list->element = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}
//增加元素
void ConsequentialListInsert(ConsequentialList* list, int pos, elemtype element){
    if(pos < 0 || pos > list->size)
        return ;
    elemtype* Newlist = (elemtype* ) realloc(list->element, sizeof(list->capacity)*2);
    list->element = Newlist;
    for(int i = pos; i < list->size; ++i){
        list->element[i+1] = list->element[i];
    }
    list->element[pos] = element;
    ++list->size;
}
//删除元素
void ConsequentialListDelete(ConsequentialList* list, int pos){
    if(pos < 0 || pos > list->size)
        return ;
    for(int i = pos; i < list->size - 1; ++i){
        list->element[i] = list->element[i+1];
    }
    --list->size;
}
//修改指定位置元素
void ConsequentialListSet(ConsequentialList* list, int pos, elemtype element){
    if(pos < 0 || pos > list->size)
        return ;
    list->element[pos] = element;
}
//查找指定元素
int ConsequentialListFine(ConsequentialList* list, elemtype data){
    for(int i = 0; i < list->size; ++i){
        if(list->element[i] == data)
            return i;
    }
    printf("查无此元素:%d\n", data);
    return -1;
}
elemtype ConsequentialListIndex(ConsequentialList* list, int index){
    if(index < 0 || index > list->size)
        return -13215;
    return list->element[index];
}
void ConsequentialListPrint(ConsequentialList* list){
    if(list->element)
        for(int i = 0; i < list->size; ++i){
            printf("%d\n", list->element[i]);
        }
    else printf("error");
}
//测试用例
int main(void){
    ConsequentialList list1;
    ConsequentialListCreate(&list1, 1);
    ConsequentialListInsert(&list1, 0, 0);
    ConsequentialListInsert(&list1, 1, 10);
    ConsequentialListInsert(&list1, 2, 20);
    ConsequentialListInsert(&list1, 3, 30);
    ConsequentialListPrint(&list1);
    ConsequentialListSet(&list1, 1, 100);
    ConsequentialListDelete(&list1, 2);
    ConsequentialListPrint(&list1);
    ConsequentialListFine(&list1, 20);
    ConsequentialListDestory(&list1);
    ConsequentialListPrint(&list1);
    return 0;
}
