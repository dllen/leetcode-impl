// 删除有序数组中的重复项 II
//

/**
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使得出现次数超过两次的元素只出现两次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
**/

#include<stdio.h>
#include<stdlib.h>
#include "common.h"

int removeDuplicates(int* nums, int numsSize) {
  if(numsSize<=2){
    return numsSize;
  }

  int slow = 2;

  for (int fast=2;fast < numsSize;fast++) {
    if(nums[fast]!=nums[slow-2]){
      nums[slow] = nums[fast];
      slow++;
    }
  }

  return slow;
}

int main()
{
  int nums[3] = {1,2,3};
  int size = 3;
  int newSize = removeDuplicates(nums, size);
  printArray(nums, newSize);
  return 0;
}
