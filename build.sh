#!/bin/bash

# 检查是否提供了参数
if [ $# -eq 0 ]; then
  echo "用法: $0 <文件名>"
  echo "示例: $0 80"
  echo "这将编译 80.c 和 common.c，生成可执行文件 80"
  exit 1
fi

# 获取输入参数
FILENAME=$1

# 检查源文件是否存在
if [ ! -f "${FILENAME}.c" ]; then
  echo "错误: 文件 ${FILENAME}.c 不存在"
  exit 1
fi

if [ ! -f "common.c" ]; then
  echo "错误: 文件 common.c 不存在"
  exit 1
fi

# 编译命令
echo "正在编译 ${FILENAME}.c 和 common.c..."
gcc -Wall -Wextra -std=c99 -g "${FILENAME}.c" common.c -o "${FILENAME}"

# 检查编译是否成功
if [ $? -eq 0 ]; then
  echo "编译成功! 生成可执行文件: ${FILENAME}"
  echo "运行命令: ./${FILENAME}"
else
  echo "编译失败!"
  exit 1
fi
