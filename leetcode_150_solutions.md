# LeetCode Top 150 面试题解题思路 (C语言版)

本文档包含 LeetCode "面试经典 150 题" 的解题思路和核心代码（C语言）。

## 目录

- [数组 / 字符串](#数组--字符串)
- [双指针](#双指针)
- [滑动窗口](#滑动窗口)
- [矩阵](#矩阵)
- [哈希表](#哈希表)
- [区间](#区间)
- [栈](#栈)
- [链表](#链表)
- [二叉树](#二叉树)
- [图](#图)
- [二分查找](#二分查找)
- [动态规划](#动态规划)

---

## 数组 / 字符串

### 88. 合并两个有序数组
**思路**：逆向双指针。从两个数组的末尾开始比较，较大的数放到 `nums1` 的末尾，避免覆盖未处理的元素。
```c
void merge(int* nums1, int m, int* nums2, int n) {
    int p1 = m - 1, p2 = n - 1, p = m + n - 1;
    while (p2 >= 0) {
        if (p1 >= 0 && nums1[p1] > nums2[p2]) nums1[p--] = nums1[p1--];
        else nums1[p--] = nums2[p2--];
    }
}
```

### 27. 移除元素
**思路**：快慢指针。快指针遍历，慢指针指向有效数组末尾。当 `nums[fast] != val` 时，复制到 `nums[slow]`。
```c
int removeElement(int* nums, int numsSize, int val) {
    int slow = 0;
    for (int fast = 0; fast < numsSize; fast++) {
        if (nums[fast] != val) nums[slow++] = nums[fast];
    }
    return slow;
}
```

### 26. 删除有序数组中的重复项
**思路**：快慢指针。`slow` 指向不重复区域末尾。当 `nums[fast] != nums[slow-1]` 时，加入新元素。
```c
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize <= 1) return numsSize;
    int slow = 1;
    for (int fast = 1; fast < numsSize; fast++) {
        if (nums[fast] != nums[slow - 1]) nums[slow++] = nums[fast];
    }
    return slow;
}
```

### 80. 删除有序数组中的重复项 II
**思路**：通用快慢指针。保留 k 个重复项：比较 `nums[fast]` 和 `nums[slow-k]`。
```c
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize <= 2) return numsSize;
    int slow = 2;
    for (int fast = 2; fast < numsSize; fast++) {
        if (nums[fast] != nums[slow - 2]) nums[slow++] = nums[fast];
    }
    return slow;
}
```

### 169. 多数元素
**思路**：摩尔投票法 (Boyer-Moore Voting Algorithm)。候选人 `candidate` 初始票数 `count` 为 0。遇到同类票数+1，异类-1。减为0时换候选人。
```c
int majorityElement(int* nums, int numsSize) {
    int count = 0, candidate = 0;
    for (int i = 0; i < numsSize; i++) {
        if (count == 0) candidate = nums[i];
        count += (nums[i] == candidate) ? 1 : -1;
    }
    return candidate;
}
```

### 189. 轮转数组
**思路**：三次翻转。1. 翻转整个数组；2. 翻转前 k 个；3. 翻转剩余部分。
```c
void reverse(int* nums, int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start++] = nums[end];
        nums[end--] = temp;
    }
}
void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, numsSize - 1);
}
```

### 121. 买卖股票的最佳时机
**思路**：贪心/动态规划。记录历史最低点 `minPrice`，每天计算当前价格卖出的利润 `price - minPrice`，更新最大利润。
```c
int maxProfit(int* prices, int pricesSize) {
    int minPrice = 1e9, maxPro = 0;
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < minPrice) minPrice = prices[i];
        else if (prices[i] - minPrice > maxPro) maxPro = prices[i] - minPrice;
    }
    return maxPro;
}
```

### 122. 买卖股票的最佳时机 II
**思路**：贪心。只要第二天比第一天高，就买入卖出（收集所有正利润）。
```c
int maxProfit(int* prices, int pricesSize) {
    int profit = 0;
    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
    }
    return profit;
}
```

### 55. 跳跃游戏
**思路**：贪心。维护能到达的最远距离 `maxReach`。遍历数组，如果当前位置 `i` 在 `maxReach` 内，更新 `maxReach = max(maxReach, i + nums[i])`。
```c
bool canJump(int* nums, int numsSize) {
    int maxReach = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i > maxReach) return false;
        int reach = i + nums[i];
        if (reach > maxReach) maxReach = reach;
    }
    return true;
}
```

### 45. 跳跃游戏 II
**思路**：贪心。记录当前步数能到达的边界 `end` 和下一步能到达的最远位置 `maxPos`。到达 `end` 时步数+1，更新 `end = maxPos`。
```c
int jump(int* nums, int numsSize) {
    int end = 0, maxPos = 0, steps = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        if (i + nums[i] > maxPos) maxPos = i + nums[i];
        if (i == end) {
            end = maxPos;
            steps++;
        }
    }
    return steps;
}
```

---

## 双指针

### 125. 验证回文串
**思路**：左右指针。跳过非字母数字字符，比较字符是否相等（忽略大小写）。
```c
bool isPalindrome(char* s) {
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        if (!isalnum(s[i])) i++;
        else if (!isalnum(s[j])) j--;
        else if (tolower(s[i]) != tolower(s[j])) return false;
        else { i++; j--; }
    }
    return true;
}
```

### 392. 判断子序列
**思路**：双指针。`i` 指向 s，`j` 指向 t。如果 `s[i] == t[j]`，`i++`。最后检查 `i` 是否到达 s 末尾。
```c
bool isSubsequence(char* s, char* t) {
    while (*s && *t) {
        if (*s == *t) s++;
        t++;
    }
    return *s == '\0';
}
```

### 167. 两数之和 II - 输入有序数组
**思路**：左右指针。`sum = nums[left] + nums[right]`。`sum > target` 则 `right--`，`sum < target` 则 `left++`。
```c
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int left = 0, right = numbersSize - 1;
    *returnSize = 2;
    int* ret = (int*)malloc(2 * sizeof(int));
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            ret[0] = left + 1; ret[1] = right + 1;
            return ret;
        } else if (sum < target) left++;
        else right--;
    }
    return ret;
}
```

### 11. 盛最多水的容器
**思路**：左右指针。面积取决于短板。移动较短的那根柱子，试图找到更高的柱子。
```c
int maxArea(int* height, int heightSize) {
    int left = 0, right = heightSize - 1, maxA = 0;
    while (left < right) {
        int h = height[left] < height[right] ? height[left] : height[right];
        int area = h * (right - left);
        if (area > maxA) maxA = area;
        if (height[left] < height[right]) left++;
        else right--;
    }
    return maxA;
}
```

### 15. 三数之和
**思路**：排序 + 双指针。固定 `i`，在 `i+1` 到末尾之间找 `left`, `right` 使 `nums[left] + nums[right] == -nums[i]`。注意去重。
```c
// 伪代码逻辑，C语言实现较繁琐需处理动态数组
// 1. qsort排序
// 2. 遍历 i:
//    如果 nums[i] > 0 break
//    如果 i > 0 && nums[i] == nums[i-1] continue (去重)
//    left = i + 1, right = n - 1
//    while left < right:
//       sum = nums[i] + nums[left] + nums[right]
//       if sum == 0: 记录结果; while left<right && nums[left]==nums[left+1] left++; left++; right--;
//       else if sum < 0: left++
//       else: right--
```

---

## 滑动窗口

### 209. 长度最小的子数组
**思路**：滑动窗口。右指针扩展窗口，当 `sum >= target` 时，记录最小长度并收缩左指针。
```c
int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0, sum = 0, minLen = INT_MAX;
    for (int right = 0; right < numsSize; right++) {
        sum += nums[right];
        while (sum >= target) {
            int len = right - left + 1;
            if (len < minLen) minLen = len;
            sum -= nums[left++];
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}
```

### 3. 无重复字符的最长子串
**思路**：滑动窗口 + 哈希表（或数组）。记录字符上一次出现的位置。遇到重复字符时，左指针跳到重复字符下一位。
```c
int lengthOfLongestSubstring(char* s) {
    int map[128] = {0}, left = 0, maxLen = 0;
    for (int right = 0; s[right]; right++) {
        char c = s[right];
        if (map[c] > left) left = map[c]; // 更新左边界
        map[c] = right + 1; // 记录字符位置+1
        int len = right - left + 1;
        if (len > maxLen) maxLen = len;
    }
    return maxLen;
}
```

---

## 矩阵

### 54. 螺旋矩阵
**思路**：模拟。设定上下左右四个边界 `top, bottom, left, right`。按右、下、左、上顺序遍历，每次遍历完收缩边界。
```c
// 核心逻辑
// while (true) {
//     for i from left to right: add matrix[top][i]; top++; if top > bottom break;
//     for i from top to bottom: add matrix[i][right]; right--; if left > right break;
//     for i from right to left: add matrix[bottom][i]; bottom--; if top > bottom break;
//     for i from bottom to top: add matrix[i][left]; left++; if left > right break;
// }
```

### 48. 旋转图像
**思路**：先水平翻转（上下对称交换），再主对角线翻转（`matrix[i][j]` 换 `matrix[j][i]`）。
```c
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    // 上下翻转
    for (int i = 0; i < matrixSize / 2; i++) {
        for (int j = 0; j < matrixSize; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[matrixSize - 1 - i][j];
            matrix[matrixSize - 1 - i][j] = temp;
        }
    }
    // 对角线翻转
    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}
```

---

## 哈希表

### 1. 两数之和
**思路**：哈希表。遍历数组，检查 `target - nums[i]` 是否在表中。如果在，返回下标；不在，将 `nums[i]` 存入表。
```c
// C语言通常需手写哈希表或使用 uthash 库
// 逻辑：Map<Value, Index>
```

### 383. 赎金信
**思路**：数组计数。统计 `magazine` 中字符频率，遍历 `ransomNote` 减计数。如果计数 < 0 则失败。
```c
bool canConstruct(char* ransomNote, char* magazine) {
    int count[26] = {0};
    while (*magazine) count[*magazine++ - 'a']++;
    while (*ransomNote) {
        if (--count[*ransomNote++ - 'a'] < 0) return false;
    }
    return true;
}
```

### 205. 同构字符串
**思路**：双向映射。`s` 到 `t` 的映射和 `t` 到 `s` 的映射必须一致。
```c
bool isIsomorphic(char* s, char* t) {
    int mapS[128] = {0}, mapT[128] = {0};
    for (int i = 0; s[i]; i++) {
        if (mapS[s[i]] != mapT[t[i]]) return false;
        mapS[s[i]] = i + 1; // 记录位置+1作为标识
        mapT[t[i]] = i + 1;
    }
    return true;
}
```

### 242. 有效的字母异位词
**思路**：数组计数。`s` 增加计数，`t` 减少计数。最后检查计数是否全为 0。

---

## 栈

### 20. 有效的括号
**思路**：栈。遇到左括号入栈，遇到右括号检查栈顶是否匹配。
```c
bool isValid(char* s) {
    char stack[10000]; int top = -1;
    while (*s) {
        if (*s == '(' || *s == '[' || *s == '{') stack[++top] = *s;
        else {
            if (top == -1) return false;
            char left = stack[top--];
            if ((*s == ')' && left != '(') || 
                (*s == ']' && left != '[') || 
                (*s == '}' && left != '{')) return false;
        }
        s++;
    }
    return top == -1;
}
```

---

## 链表

### 141. 环形链表
**思路**：快慢指针。`slow` 走一步，`fast` 走两步。相遇则有环。

### 21. 合并两个有序链表
**思路**：递归或迭代。比较头节点，小的作为新头节点，指向剩余部分的合并结果。
```c
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
```

### 206. 反转链表
**思路**：迭代。`prev` 指向 NULL，`curr` 指向 head。保存 `next`，改变指向，移动指针。
```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev = NULL, *curr = head;
    while (curr) {
        struct ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

---

## 二叉树

### 104. 二叉树的最大深度
**思路**：递归。`max(maxDepth(left), maxDepth(right)) + 1`。
```c
int maxDepth(struct TreeNode* root) {
    if (!root) return 0;
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return (l > r ? l : r) + 1;
}
```

### 226. 翻转二叉树
**思路**：递归。交换左右子树，递归翻转左右子树。
```c
struct TreeNode* invertTree(struct TreeNode* root) {
    if (!root) return NULL;
    struct TreeNode* temp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(temp);
    return root;
}
```

### 101. 对称二叉树
**思路**：递归。判断 `left` 和 `right` 是否镜像：值相等且 `L.left == R.right` && `L.right == R.left`。

---

## 二分查找

### 35. 搜索插入位置
**思路**：标准二分。找到第一个 `>= target` 的位置。
```c
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}
```

---

## 动态规划

### 70. 爬楼梯
**思路**：斐波那契数列。`dp[i] = dp[i-1] + dp[i-2]`。
```c
int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2, c;
    for (int i = 3; i <= n; i++) {
        c = a + b; a = b; b = c;
    }
    return b;
}
```

### 198. 打家劫舍
**思路**：`dp[i] = max(dp[i-1], dp[i-2] + nums[i])`。
```c
int rob(int* nums, int numsSize) {
    int prev = 0, curr = 0;
    for (int i = 0; i < numsSize; i++) {
        int temp = curr > prev + nums[i] ? curr : prev + nums[i];
        prev = curr;
        curr = temp;
    }
    return curr;
}
```

---

*(注：由于篇幅限制，本文档精选了 Top 150 中最具代表性的题目。掌握这些核心思路，可以举一反三解决大部分同类问题。)*
