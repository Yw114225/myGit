#include <stdlib.h>
#include <string.h>
#include "../inc/hash.h"

hashtable* HashInit()
{
    hashtable* HT;
    if((HT = (hashtable*)malloc(sizeof(hashtable))) == NULL){
        printf("malloc hashtable failed\n");
        return NULL;
    }
    memset(HT, 0, sizeof(hashtable));

    return HT;
}

//hash插入，返回hash表的存储头
int HashInsert(hashtable* HT, DS key)
{
    if(HT == NULL){
        printf("Insert failed\n");
        return -1;
    }

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if(newNode == NULL)
        return -1;
    newNode->key = key;
    newNode->val = key % N;
    newNode->next = NULL;
    
    ListNode* temp = NULL;
    temp = &(HT->data[newNode->val]);
    while(temp->next && temp->next->key < newNode->key){
            temp = temp->next;
    }
    if(temp != NULL){
        newNode->next = temp->next;
        temp->next = newNode;
    }
    else
        temp = newNode;
    return newNode->val;
}


int HashDelete(hashtable* HT, DS key)
{

}

ListNode* HashIndex(hashtable* HT, DS key)
{
    if(HT == NULL){
        printf("HT is NULL\n");
        return NULL;
    }
    ListNode* temp = &(HT->data[key % N]);
    while(temp->next && temp->next->key != key){
        printf("%d %d", temp->next->key, key);
        temp = temp->next;
    }
    if(temp == NULL)
        return NULL;
    else{
        printf("found\n");
        return temp->next;
    }
}
