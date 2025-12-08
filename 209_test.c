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

void test(int target, int *nums, int numsSize, int expected) {
  int result = minSubArrayLen(target, nums, numsSize);
  printf("target=%d, result=%d, expected=%d, %s\n", target, result, expected,
         result == expected ? "✓" : "✗");
}

int main() {
  // Test case 1: target=11, nums=[1,2,3,4,5]
  int nums1[] = {1, 2, 3, 4, 5};
  test(11, nums1, 5, 3); // [3,4,5] sum=12, length=3

  // Test case 2: target=7, nums=[2,3,1,2,4,3]
  int nums2[] = {2, 3, 1, 2, 4, 3};
  test(7, nums2, 6, 2); // [4,3] sum=7, length=2

  // Test case 3: target=4, nums=[1,4,4]
  int nums3[] = {1, 4, 4};
  test(4, nums3, 3, 1); // [4] sum=4, length=1

  // Test case 4: target=11, nums=[1,1,1,1,1,1,1,1]
  int nums4[] = {1, 1, 1, 1, 1, 1, 1, 1};
  test(11, nums4, 8, 0); // No subarray, return 0

  // Test case 5: target=15, nums=[1,2,3,4,5]
  int nums5[] = {1, 2, 3, 4, 5};
  test(15, nums5, 5, 5); // [1,2,3,4,5] sum=15, length=5

  return 0;
}
