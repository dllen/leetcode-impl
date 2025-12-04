# LeetCode 快慢指针解题教程

## 📚 目录
1. [什么是快慢指针](#什么是快慢指针)
2. [核心思想](#核心思想)
3. [经典应用场景](#经典应用场景)
4. [解题模板](#解题模板)
5. [典型例题详解](#典型例题详解)
6. [练习题目清单](#练习题目清单)

---

## 什么是快慢指针

**快慢指针**（Fast-Slow Pointer），也称为**双指针技术**，是一种高效的算法技巧。它使用两个指针以不同的速度遍历数据结构（通常是数组或链表）。

### 基本特征
- **慢指针（Slow）**：移动速度较慢，通常用于标记位置或存储结果
- **快指针（Fast）**：移动速度较快，用于遍历或查找元素
- **时间复杂度**：通常为 O(n)
- **空间复杂度**：通常为 O(1)

---

## 核心思想

快慢指针的核心在于**用空间换时间的逆向思维**——通过巧妙的指针移动策略，在 O(1) 空间复杂度下解决原本需要额外空间的问题。

### 关键原则
1. **职责分离**：快指针负责"探索"，慢指针负责"记录"
2. **原地修改**：直接在原数组/链表上操作，避免额外空间
3. **相对速度**：利用两个指针的速度差解决问题

---

## 经典应用场景

### 1️⃣ 数组去重/删除元素
**场景**：在有序数组中删除重复项或特定元素  
**策略**：慢指针指向结果数组的末尾，快指针遍历查找有效元素

### 2️⃣ 链表环检测
**场景**：判断链表是否有环  
**策略**：快指针每次走2步，慢指针每次走1步，如果有环则必定相遇

### 3️⃣ 寻找中间节点
**场景**：找到链表的中间节点  
**策略**：快指针走2步，慢指针走1步，快指针到末尾时慢指针在中间

### 4️⃣ 滑动窗口
**场景**：子数组/子串问题  
**策略**：快指针扩展窗口，慢指针收缩窗口

---

## 解题模板

### 模板一：数组去重/删除元素

```c
int removeElements(int* nums, int numsSize, int condition) {
    // 边界处理
    if (numsSize == 0) return 0;
    
    // 初始化双指针
    int slow = 0;  // 慢指针：指向结果数组的下一个位置
    int fast = 0;  // 快指针：遍历原数组
    
    // 快指针遍历整个数组
    while (fast < numsSize) {
        // 如果当前元素满足保留条件
        if (shouldKeep(nums[fast])) {
            nums[slow] = nums[fast];  // 保存到结果位置
            slow++;                    // 慢指针前进
        }
        fast++;  // 快指针始终前进
    }
    
    return slow;  // 慢指针的位置即为新数组长度
}
```

### 模板二：链表环检测

```c
bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    
    struct ListNode *slow = head;       // 慢指针：每次走1步
    struct ListNode *fast = head->next; // 快指针：每次走2步
    
    while (slow != fast) {
        // 快指针到达末尾，说明无环
        if (fast == NULL || fast->next == NULL) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return true;  // 相遇说明有环
}
```

### 模板三：寻找链表中间节点

```c
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    // 快指针走2步，慢指针走1步
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // 慢指针指向中间节点
}
```

---

## 典型例题详解

### 例题 1：删除有序数组中的重复项（LeetCode 26）

**题目**：给定一个有序数组，删除重复项，使每个元素只出现一次，返回新长度。

**分析**：
- 有序数组，重复元素必定相邻
- 慢指针指向不重复元素的末尾
- 快指针遍历查找新的不重复元素

**代码实现**：

```c
int removeDuplicates(int* nums, int numsSize) {
    // 边界处理
    if (numsSize <= 1) {
        return numsSize;
    }
    
    // 慢指针从1开始，因为第一个元素总是保留
    int slow = 1;
    int fast = 1;
    
    while (fast < numsSize) {
        // 如果当前元素与上一个保留的元素不同
        if (nums[fast] != nums[slow - 1]) {
            nums[slow] = nums[fast];  // 保存新元素
            slow++;
        }
        fast++;
    }
    
    return slow;
}
```

**图解过程**（以 `[1,1,2,2,3]` 为例）：

```
初始: [1, 1, 2, 2, 3]
       ↑  ↑
      s-1 s,f

步骤1: nums[1]=1 == nums[0]=1，跳过
       [1, 1, 2, 2, 3]
       ↑  ↑  ↑
      s-1 s  f

步骤2: nums[2]=2 != nums[0]=1，保留
       [1, 2, 2, 2, 3]
       ↑  ↑     ↑
      s-1 s     f

步骤3: nums[3]=2 == nums[1]=2，跳过
       [1, 2, 2, 2, 3]
          ↑  ↑     ↑
         s-1 s     f

步骤4: nums[4]=3 != nums[1]=2，保留
       [1, 2, 3, 2, 3]
          ↑  ↑        ↑
         s-1 s        f

结果: [1, 2, 3]，长度为3
```

---

### 例题 2：移除元素（LeetCode 27）

**题目**：给定数组和值 val，原地移除所有等于 val 的元素，返回新长度。

**分析**：
- 不需要保持相对顺序
- 慢指针指向结果数组末尾
- 快指针遍历查找不等于 val 的元素

**代码实现**：

```c
int removeElement(int* nums, int numsSize, int val) {
    int slow = 0;
    int fast = 0;
    
    while (fast < numsSize) {
        // 如果当前元素不等于 val，保留
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;  // 等于 val 的元素被跳过
    }
    
    return slow;
}
```

**关键点**：
- 当 `nums[fast] == val` 时，只有 fast 前进，slow 不动
- 这样就"跳过"了需要删除的元素

---

### 例题 3：合并两个有序数组（LeetCode 88）

**题目**：给定两个有序数组 nums1 和 nums2，将 nums2 合并到 nums1 中。

**分析**：
- 从后往前填充，避免覆盖未处理的元素
- 三个指针：p1（nums1末尾）、p2（nums2末尾）、p（合并位置）

**代码实现**：

```c
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int p1 = m - 1;      // nums1 的最后一个有效元素
    int p2 = n - 1;      // nums2 的最后一个元素
    int p = m + n - 1;   // 合并后的最后位置
    
    // 从后往前填充
    while (p1 >= 0 && p2 >= 0) {
        if (nums1[p1] > nums2[p2]) {
            nums1[p] = nums1[p1];
            p1--;
        } else {
            nums1[p] = nums2[p2];
            p2--;
        }
        p--;
    }
    
    // 如果 nums2 还有剩余元素
    while (p2 >= 0) {
        nums1[p] = nums2[p2];
        p2--;
        p--;
    }
    // nums1 剩余元素已经在正确位置，无需处理
}
```

---

### 例题 4：环形链表（LeetCode 141）

**题目**：判断链表是否有环。

**分析**：
- 快指针每次走2步，慢指针每次走1步
- 如果有环，快慢指针必定相遇
- 如果无环，快指针会先到达末尾

**代码实现**：

```c
bool hasCycle(struct ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    
    struct ListNode *slow = head;
    struct ListNode *fast = head->next;
    
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL) {
            return false;  // 快指针到达末尾，无环
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return true;  // 相遇，有环
}
```

**为什么快慢指针一定会相遇？**
- 假设环的长度为 L
- 当慢指针进入环时，快指针已经在环内某处
- 每次迭代，快指针与慢指针的距离减少1
- 最多 L 次迭代后，距离变为0，即相遇

---

### 例题 5：链表的中间节点（LeetCode 876）

**题目**：返回链表的中间节点，如果有两个中间节点，返回第二个。

**代码实现**：

```c
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

**图解**：
```
链表: 1 -> 2 -> 3 -> 4 -> 5
      ↑              ↑
     slow           fast

步骤1: slow=2, fast=3
步骤2: slow=3, fast=5
步骤3: fast->next=NULL，结束
返回: slow=3（中间节点）
```

---

## 解题技巧总结

### 🎯 技巧 1：指针初始化
- **数组去重**：slow 和 fast 都从 0 或 1 开始
- **链表环检测**：fast 从 head->next 开始，避免初始就相等
- **寻找中间节点**：都从 head 开始

### 🎯 技巧 2：循环条件
- **数组**：`while (fast < numsSize)`
- **链表**：`while (fast != NULL && fast->next != NULL)`
- **环检测**：`while (slow != fast)`

### 🎯 技巧 3：边界处理
- 空数组/链表
- 单元素数组/链表
- 所有元素都需要删除的情况

### 🎯 技巧 4：指针移动策略
| 场景 | 慢指针移动 | 快指针移动 |
|------|-----------|-----------|
| 数组去重 | 条件满足时+1 | 每次+1 |
| 环检测 | 每次+1 | 每次+2 |
| 中间节点 | 每次+1 | 每次+2 |

---

## 练习题目清单

### 🔰 入门级（必做）
1. ✅ [26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)
2. ✅ [27. 移除元素](https://leetcode.cn/problems/remove-element/)
3. ✅ [88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)
4. [141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/)
5. [876. 链表的中间节点](https://leetcode.cn/problems/middle-of-the-linked-list/)

### 🔸 进阶级
6. [80. 删除有序数组中的重复项 II](https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/)（保留2个）
7. [142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)（找环的入口）
8. [283. 移动零](https://leetcode.cn/problems/move-zeroes/)
9. [344. 反转字符串](https://leetcode.cn/problems/reverse-string/)
10. [19. 删除链表的倒数第N个节点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)

### 🔺 挑战级
11. [234. 回文链表](https://leetcode.cn/problems/palindrome-linked-list/)
12. [287. 寻找重复数](https://leetcode.cn/problems/find-the-duplicate-number/)
13. [202. 快乐数](https://leetcode.cn/problems/happy-number/)
14. [457. 环形数组循环](https://leetcode.cn/problems/circular-array-loop/)

---

## 常见错误与避坑指南

### ❌ 错误 1：指针初始化错误
```c
// 错误：两个指针都从0开始，第一个元素会被跳过
int slow = 0, fast = 0;
while (fast < n) {
    if (nums[fast] != nums[slow]) {  // 第一次比较 nums[0] == nums[0]
        nums[slow++] = nums[fast];
    }
    fast++;
}
```

**正确做法**：
```c
// 方法1：slow 从 1 开始
int slow = 1, fast = 1;
while (fast < n) {
    if (nums[fast] != nums[slow-1]) {
        nums[slow++] = nums[fast];
    }
    fast++;
}

// 方法2：先处理第一个元素
int slow = 0, fast = 1;
while (fast < n) {
    if (nums[fast] != nums[slow]) {
        nums[++slow] = nums[fast];
    }
    fast++;
}
```

### ❌ 错误 2：忘记边界检查
```c
// 错误：可能访问 fast->next->next 导致空指针
while (fast != NULL) {
    fast = fast->next->next;  // 如果 fast->next 为 NULL，崩溃！
}
```

**正确做法**：
```c
while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;
}
```

### ❌ 错误 3：返回值错误
```c
// 错误：返回 slow - 1
return slow - 1;  // slow 已经指向下一个位置，不需要减1
```

**正确做法**：
```c
return slow;  // slow 本身就是新数组的长度
```

---

## 学习路径建议

### 第1天：理解基础
- 阅读本教程的前3章
- 完成 LeetCode 26、27

### 第2天：数组操作
- 完成 LeetCode 88、283
- 尝试自己画图理解指针移动

### 第3天：链表基础
- 完成 LeetCode 141、876
- 理解链表快慢指针的特殊性

### 第4天：进阶练习
- 完成 LeetCode 80、142
- 总结不同题型的模板差异

### 第5天：综合应用
- 完成剩余挑战题
- 尝试优化已做题目的代码

---

## 总结

快慢指针是一种**简单但强大**的算法技巧，掌握它的关键在于：

1. **理解本质**：用两个速度不同的指针解决问题
2. **熟记模板**：数组去重、链表环检测、中间节点等模板
3. **大量练习**：从简单到复杂，逐步提升
4. **画图辅助**：遇到困难时，画图模拟指针移动过程

> 💡 **记住**：快慢指针的核心是**职责分离** —— 快指针探索，慢指针记录！

---

## 参考资源

- [LeetCode 官方题解](https://leetcode.cn/problemset/all/)
- [代码随想录 - 双指针专题](https://programmercarl.com/)
- 本地实现代码：[26.c](file:///Users/shichaopeng/Work/test/leetcode-impl/26.c)、[27.c](file:///Users/shichaopeng/Work/test/leetcode-impl/27.c)、[88.c](file:///Users/shichaopeng/Work/test/leetcode-impl/88.c)

---

**祝你刷题顺利！加油！💪**
