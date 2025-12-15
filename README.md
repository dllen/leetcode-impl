# LeetCode C Solutions

This repository contains C implementations for various LeetCode problems. The solutions are designed with a focus on efficiency (time and space complexity).

## 🛠 Project Build Tool

A shell script `build_advanced.sh` is provided to compile and run the solutions easily.

### Usage

```bash
./build_advanced.sh [options] <problem_id>
```

### Options

*   `-h`, `--help`: Display help information.
*   `-r`, `--run`: Automatically run the program after compilation.
*   `-c`, `--clean`: Clean up old executables before compiling.
*   `-d`, `--debug`: Enable debug mode (adds more compilation flags).

### Examples

Compile and run problem 189:
```bash
./build_advanced.sh -c -r 189
```

Just compile problem 88:
```bash
./build_advanced.sh 88
```

---

## 📝 Problem Solutions & Strategies

### [26. Remove Duplicates from Sorted Array](26.c)
*   **Strategy**: Two Pointers (Slow & Fast).
*   **Approach**: Use a slow pointer `i` to track the position of unique elements and a fast pointer `j` to scan the array. When `nums[j]` is different from `nums[i-1]`, verify it as a new unique element.
*   **Complexity**: Time O(n), Space O(1).

### [27. Remove Element](27.c)
*   **Strategy**: Two Pointers.
*   **Approach**: Use a write pointer to keep track of the array valid size. Iterate through the array; if an element is not equal to `val`, copy it to the write pointer's position and increment the pointer.
*   **Complexity**: Time O(n), Space O(1).

### [55. Jump Game](55.c)
*   **Strategy**: Greedy.
*   **Approach**: Maintain a variable `maxIndex` representing the furthest reachable index. Iterate through the array; if the current index is reachable (`i <= maxIndex`), update `maxIndex` to `max(maxIndex, i + nums[i])`.
*   **Complexity**: Time O(n), Space O(1).


### [80. Remove Duplicates from Sorted Array II](80.c)
*   **Strategy**: Two Pointers (with at most 2 duplicates).
*   **Approach**: Similar to Problem 26, but compare the current element with the element at `index - 2` instead of `index - 1`. If `nums[i] != nums[index - 2]`, it means we haven't used up the quota of 2 allowed duplicates for that value.
*   **Complexity**: Time O(n), Space O(1).

### [88. Merge Sorted Array](88.c)
*   **Strategy**: Three Pointers (Reverse iteration).
*   **Approach**: Use pointers `p1` and `p2` for the ends of initialized parts of `nums1` and `nums2`, and `p` for the end of the total array `nums1`. Compare elements from the back and place the larger one at `p` to avoid overwriting elements in `nums1`.
*   **Complexity**: Time O(m+n), Space O(1).

### [121. Best Time to Buy and Sell Stock](121.c)
*   **Strategy**: One Pass (Greedy).
*   **Approach**: Iterate through prices while maintaining the minimum purchase price seen so far (`minPrice`). For every price, calculate the potential profit (`price - minPrice`) and update `maxProfit` if it's higher.
*   **Complexity**: Time O(n), Space O(1).

### [122. Best Time to Buy and Sell Stock II](122.c)
*   **Strategy**: One Pass (Greedy).
*   **Approach**: Sum up all positive differences between consecutive days (`prices[i] - prices[i-1]`). This captures all ascending price trends.
*   **Complexity**: Time O(n), Space O(1).



### [125. Valid Palindrome](125.c)
*   **Strategy**: Two Pointers.
*   **Approach**: Use two pointers starting from both ends of the string. Move them towards each other, skipping non-alphanumeric characters. Compare the remaining characters case-insensitively. Use `isalnum` (C++) or `Character.isLetterOrDigit` (Java) to check for valid characters.
*   **Complexity**: Time O(n), Space O(1).

### [169. Majority Element](169.c)
*   **Strategy**: Boyer-Moore Voting Algorithm.
*   **Approach**: Maintain a `candidate` and a `count`. If `count` is 0, pick the current number as candidate. Increment count if the current number matches the candidate, otherwise decrement. The survivor is the majority element.
*   **Complexity**: Time O(n), Space O(1).

### [189. Rotate Array](189.c)
*   **Strategy**: Three Reversals.
*   **Approach**: 
    1. Reverse the entire array.
    2. Reverse the first `k` elements.
    3. Reverse the remaining `n-k` elements.
*   **Complexity**: Time O(n), Space O(1).

### [290. Word Pattern](290.c)
*   **Strategy**: Hash Map (Bijection Mapping).
*   **Approach**: Split string `s` into tokens using `strtok`. Use an array to map pattern characters to words. Verify that each pattern character maps to a unique word and vice-versa (bijection).
*   **Complexity**: Time O(N), Space O(N).
