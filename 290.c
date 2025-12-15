/**
    290.单词规律
    给定一个模式 pattern 和一个字符串 s ，请你判断 s 是否遵循模式 pattern 。
    如果遵循，返回 true ；否则返回 false 。
    模式中的字符必须与字符串中的字符一一对应。
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool wordPattern(char* pattern, char* s) {
    char *words[3000]; // Array to store words split from s
    int word_count = 0;
    
    // Split string s by space
    char *token = strtok(s, " ");
    while (token != NULL) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }
    // Check if lengths match
    if (strlen(pattern) != (size_t)word_count) {
        return false;
    }
    
    char *p2w[26] = {NULL};
    
    for (int i = 0; i < word_count; i++) {
        int p_idx = pattern[i] - 'a';
        char *word = words[i];
        
        if (p2w[p_idx] != NULL) {
            // If pattern char is already mapped, check if it maps to the same word
            if (strcmp(p2w[p_idx], word) != 0) {
                return false;
            }
        } else {
            // If pattern char is not mapped, check if the word is already mapped to another pattern char
            for (int j = 0; j < 26; j++) {
                if (p2w[j] != NULL && strcmp(p2w[j], word) == 0) {
                    return false;
                }
            }
            p2w[p_idx] = word;
        }
    }
    
    return true;
}

int main(){
    char pattern1[] = "abba";
    char s1[] = "dog cat cat dog";
    printf("Test 1 (Expected 1): %d\n", wordPattern(pattern1, s1));

    char pattern2[] = "abba";
    char s2[] = "dog cat cat fish";
    printf("Test 2 (Expected 0): %d\n", wordPattern(pattern2, s2));

    char pattern3[] = "aaaa";
    char s3[] = "dog cat cat dog";
    printf("Test 3 (Expected 0): %d\n", wordPattern(pattern3, s3));

    char pattern4[] = "abba";
    char s4[] = "dog dog dog dog";
    printf("Test 4 (Expected 0): %d\n", wordPattern(pattern4, s4));
    
    char pattern5[] = "abc";
    char s5[] = "dog cat dog";
    printf("Test 5 (Expected 0): %d\n", wordPattern(pattern5, s5));

    return 0;
}
