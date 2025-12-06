/**
    55. 跳跃游戏
    给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
    数组中的每个元素代表你在该位置可以跳跃的最大长度。
    判断你是否能够到达最后一个下标。

 */

#include <math.h>
#include <stdio.h>

bool canJump(int *nums, int numsSize) {
  int maxIndex = 0;
  for (int i = 0; i < numsSize; i++) {
    if (i > maxIndex) {
      return false;
    }
    maxIndex = fmax(maxIndex, i + nums[i]);
  }
  return true;
}

int main() {
  int nums[] = {2, 3, 1, 1, 4};
  int numsSize = sizeof(nums) / sizeof(nums[0]);
  printf("%d\n", canJump(nums, numsSize));
  return 0;
}
