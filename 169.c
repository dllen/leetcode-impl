/**
  多数元素
  给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
  你可以假设数组是非空的，并且给定的数组总是存在多数元素。

  使用 Boyer-Moore 投票算法 (Boyer-Moore Voting Algorithm) 实现了多数元素查找。该算法的核心思想是利用“对拼消耗”：如果是众数，它的数量超过总数的一半，那么即使它与其他所有非众数一一抵消，最后剩下的也一定是众数。
  算法特点：
  时间复杂度：O(n)，只需要遍历数组一次。
  空间复杂度：O(1)，只需要常数个变量 (count 和 candidate) 来维护状态。

 **/

#include<stdio.h>
#include<stdlib.h>

int majorityElement(int* nums, int numsSize) 
{
    int count = 0;
    int candidate = 0;

    for (int i = 0; i < numsSize; i++) {
        if (count == 0) {
            candidate = nums[i];
        }
        count += (nums[i] == candidate) ? 1 : -1;
    }

    return candidate;
}



int main()
{
    int nums[] = {2,2,1,1,1,2,2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    printf("%d\n", majorityElement(nums, numsSize));
    return 0;
}
