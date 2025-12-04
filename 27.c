// 移除元素

#include <stdio.h>
#include <stdlib.h>

int removeElement(int* nums, int numsSize, int val) 
{
  // Initialize two pointers:
  // 'i' will track the position to place the next non-`val` element (the "slow" pointer).
  // 'j' will iterate through the array to find elements (the "fast" pointer).
  int i = 0;
  int j = 0;
  // Iterate through the array with pointer 'j'.
  while(j < numsSize) {
    // If the current element `nums[j]` is not equal to the value `val` to be removed,
    // it means this element should be kept.
    if(nums[j] != val) {
      // Place this element at the position indicated by 'i'
      // and then increment 'i' to prepare for the next non-`val` element.
      nums[i++] = nums[j];
    }
    // Always increment 'j' to move to the next element in the original array.
    // If nums[j] == val, it is effectively "skipped" as 'i' is not incremented.
    j++;
  }
  // The pointer 'i' now represents the new length of the array
  // after removing all occurrences of `val`.
  return i;
}

int main()
{
  int nums[] = {3, 2, 2, 3};
  int numsSize = 4;
  int val = 3;
  int ret = removeElement(nums, numsSize, val);
  for(int i = 0; i < ret; i++) {
    printf("%d ", nums[i]);
  }
  return 0;
}
