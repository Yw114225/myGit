#include "../inc/qsort.h"
int partion(int* arr, int low, int high){
    int temp = arr[low];
    while(low < high){
	while(low < high && temp <= arr[high])
	    --high;
	arr[low] = arr[high];
	while(low < high && temp >= arr[low])
	    ++low;
	arr[high] = arr[low];
    }
    arr[low] = temp;
    return low;
}


int* qsort(int* arr, int low, int high)
{
    if(arr == NULL){
	printf("arr is NULL\n");
	return NULL;
    }

    if(low >= high)
	return arr;

    int basep = partion(arr, low, high);
    qsort(arr, basep + 1, high);
    qsort(arr, low, basep - 1);
    
    return arr;

}
