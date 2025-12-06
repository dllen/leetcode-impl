/**
 * 125. 验证回文串
 * 给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
 * java : Character.isLetterOrDigit(char ch)
 * c++ : isalnum(char ch)
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isPalindrome(char *s) {
  int left = 0;
  int right = strlen(s) - 1;
  while (left < right) {
    if (!isalnum(s[left])) {
      left++;
    } else if (!isalnum(s[right])) {
      right--;
    } else if (tolower(s[left]) != tolower(s[right])) {
      return false;
    } else {
      left++;
      right--;
    }
  }
  return true;
}

int main() {
  char s[] = "A man, a plan, a canal: Panama";
  printf("%d\n", isPalindrome(s));
  return 0;
}