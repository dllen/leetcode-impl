// 删除有序数组中的重复项

#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) 
{
    // 处理空数组或单元素数组的边界情况
    if(numsSize <= 1) {
        return numsSize;
    }
    
    // 初始化两个指针：
    // 'i' 指向下一个不重复元素应该放置的位置（慢指针），从1开始因为第一个元素总是保留
    // 'j' 用于遍历整个数组（快指针），从1开始与前面的元素比较
    int i = 1;
    int j = 1;
    
    // 使用快指针 'j' 遍历数组
    while(j < numsSize) {
        // 如果当前元素 nums[j] 与上一个保留的元素 nums[i-1] 不相同，说明找到了新的不重复元素
        if(nums[j] != nums[i-1]) {
            // 将新的不重复元素放到位置 i，并递增 i
            nums[i] = nums[j];
            i++;
        }
        // 快指针 j 始终向前移动，扫描下一个元素
        // 如果 nums[j] == nums[i-1]，则跳过该重复元素（i 不递增）
        j++;
    }
    
    // 返回不重复元素的个数（即 i 的最终位置）
    return i;
}

int main()
{
    int nums[] = {1, 1, 2};
    int numsSize = 3;
    int ret = removeDuplicates(nums, numsSize);
    for(int i = 0; i < ret; i++) {
        printf("%d ", nums[i]);
    }
    return 0;
}
