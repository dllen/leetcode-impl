/**
 * 209. 长度最小的子数组
 * 给定一个含有 n 个正整数的数组和一个正整数 target 。
 * 找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1,
 * ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

问题分析
原来的代码使用了暴力枚举方法（O(n²)时间复杂度），虽然逻辑基本正确，但效率不高。

解决方案
使用了**滑动窗口（双指针）**算法，时间复杂度优化到 O(n)：

右指针扩展窗口：不断向右移动 right 指针，将元素加入窗口
左指针收缩窗口：当窗口和 sum >= target 时，尝试收缩左边界来找到最小长度
记录最小值：每次满足条件时更新最小长度

 * */

#include <stdio.h>

int minSubArrayLen(int target, int *nums, int numsSize) {
  int left = 0;
  int sum = 0;
  int res = 0;

  for (int right = 0; right < numsSize; right++) {
    sum += nums[right];

    while (sum >= target) {
      int len = right - left + 1;
      if (res == 0 || len < res) {
        res = len;
      }
      sum -= nums[left];
      left++;
    }
  }

  return res;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5};
  int numsSize = 5;
  int r = minSubArrayLen(11, nums, numsSize);
  printf("%d\n", r);
  return 0;
}
