#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 数组操作相关函数
void printArray(int* nums, int size);

// 字符串操作相关函数
int stringLength(const char* str);
char* stringCopy(const char* src);
int stringCompare(const char* str1, const char* str2);

// 数学计算相关函数
int max(int a, int b);
int min(int a, int b);
int factorial(int n);

// 内存管理相关函数
void* safeMalloc(size_t size);
void safeFree(void** ptr);

#endif // COMMON_H
