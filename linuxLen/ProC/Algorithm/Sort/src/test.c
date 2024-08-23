#include "../inc/qsort.h"
#include <stdio.h>
#include <stdio.h>

#define N 15

int main(int argc, char* argv[])
{
    int arr[N] = {};
    
    //生成随机数数组
    srandom(10);
    for(int i = 0; i < N; ++i){
	arr[i] = random() % 100;
    }
    
    for(int i = 0; i < N; ++i){
	if(i == 0)
	    printf("排序前:");
	printf("%d ", arr[i]);
    }
    puts("\n");
    int* ret = qsort(arr, 0, N-1); 
    for(int i = 0; i < N; ++i){
	if(i == 0)
	    printf("排序后:");
	printf("%d ", *(ret+i));
    }
    puts("");


    return 0;
}
