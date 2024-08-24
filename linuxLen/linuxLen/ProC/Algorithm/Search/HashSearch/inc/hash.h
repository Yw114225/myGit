#include <stdio.h>
#define N 15

typedef int DS;

//节点
typedef struct Node{
    struct Node* next;
    DS  key;
    DS  val;
}ListNode;

//hash表
typedef struct{
    ListNode data[N];
}hashtable;

hashtable* HashInit();
int HashInsert(hashtable* HT, DS key);
int HashDelete(hashtable* HT, DS key);
ListNode* HashIndex(hashtable* HT, DS key);
