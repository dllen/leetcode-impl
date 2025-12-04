
#include<stdio.h>
#include "common.h"

void printArray(int* nums, int size)
{
  printf("[");
  for (int i=0;i<size;i++){
    printf("%d", nums[i]);
    if(i < size-1){
      printf(", ");
    }
  }
  printf("]\n");
}
