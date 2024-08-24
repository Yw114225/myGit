#include "../inc/hash.h"

int main(int argc, char* argv[])
{
    hashtable* HT = HashInit();
    ListNode* ret = NULL;
    int key;
    int arr[] = {23,34,14,38,46,16,68,15,7,31,26};
    if(HT == NULL){
        printf("Create hash failed\n");
        return -1;
    }
    //哈希表插入
    for(int i = 0; i < sizeof(arr)/sizeof(int); ++i){
        HashInsert(HT, arr[i]);
    }
    printf("%d ", HT->data[1].key);
    //哈希表检索
    printf("input what you wanna index:\n");
    scanf("%d", &key);
    ret = HashIndex(HT, key);
    if(ret == NULL)
        printf("not found\n");
    else printf("found:%d %d\n", key, ret->key);
    return 0;
}
