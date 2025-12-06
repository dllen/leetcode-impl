/**
    给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
    三次翻转法 (Three Reversals) 实现了数组轮转

    算法思路
        假设数组为 nums = [1, 2, 3, 4, 5, 6, 7]，k = 3。

        翻转整体：将整个数组翻转，得到 [7, 6, 5, 4, 3, 2, 1]。
        翻转前 k 个：将前 k (3) 个元素翻转，得到 [5, 6, 7, 4, 3, 2, 1]。
        翻转后半部分：将剩余的元素翻转，得到 [5, 6, 7, 1, 2, 3, 4]。
        复杂度分析
    时间复杂度：O(n)。每个元素被翻转两次，总操作次数与 n 成线性关系。
    空间复杂度：O(1)。只使用了常数个额外变量来进行交换操作。
 */

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// 辅助函数：翻转数组指定区间 [start, end]
void reverse(int *nums, int start, int end) {
  while (start < end) {
    int temp = nums[start];
    nums[start] = nums[end];
    nums[end] = temp;
    start++;
    end--;
  }
}

void rotate(int *nums, int numsSize, int k) {
  k %= numsSize; // 处理 k > numsSize 的情况
  if (k == 0)
    return;

  // 1. 翻转整个数组
  reverse(nums, 0, numsSize - 1);
  // 2. 翻转前 k 个元素
  reverse(nums, 0, k - 1);
  // 3. 翻转剩余元素
  reverse(nums, k, numsSize - 1);
}

int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};
  rotate(nums, 7, 3);
  printArray(nums, 7);
  return 0;
}
