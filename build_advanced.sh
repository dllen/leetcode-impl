#!/bin/bash

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 显示帮助信息
show_help() {
    echo "用法: $0 [选项] <文件名>"
    echo ""
    echo "选项:"
    echo "  -h, --help     显示此帮助信息"
    echo "  -r, --run      编译后自动运行程序"
    echo "  -c, --clean    编译前清理旧的可执行文件"
    echo "  -d, --debug    启用调试模式（添加更多调试信息）"
    echo ""
    echo "示例:"
    echo "  $0 80              # 编译 80.c"
    echo "  $0 -r 80           # 编译并运行 80.c"
    echo "  $0 -c -r main      # 清理、编译并运行 main.c"
    echo ""
}

# 默认选项
RUN_AFTER_BUILD=false
CLEAN_BEFORE_BUILD=false
DEBUG_MODE=false
FILENAME=""

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -r|--run)
            RUN_AFTER_BUILD=true
            shift
            ;;
        -c|--clean)
            CLEAN_BEFORE_BUILD=true
            shift
            ;;
        -d|--debug)
            DEBUG_MODE=true
            shift
            ;;
        -*)
            echo -e "${RED}错误: 未知选项 $1${NC}"
            show_help
            exit 1
            ;;
        *)
            if [ -z "$FILENAME" ]; then
                FILENAME=$1
            else
                echo -e "${RED}错误: 只能指定一个文件名${NC}"
                exit 1
            fi
            shift
            ;;
    esac
done

# 检查是否提供了文件名
if [ -z "$FILENAME" ]; then
    echo -e "${RED}错误: 请提供文件名${NC}"
    show_help
    exit 1
fi

# 检查源文件是否存在
if [ ! -f "${FILENAME}.c" ]; then
    echo -e "${RED}错误: 文件 ${FILENAME}.c 不存在${NC}"
    exit 1
fi

if [ ! -f "common.c" ]; then
    echo -e "${RED}错误: 文件 common.c 不存在${NC}"
    exit 1
fi

# 清理旧文件
if [ "$CLEAN_BEFORE_BUILD" = true ]; then
    if [ -f "$FILENAME" ]; then
        echo -e "${YELLOW}清理旧的可执行文件: $FILENAME${NC}"
        rm "$FILENAME"
    fi
fi

# 构建编译命令
COMPILE_CMD="gcc -Wall -Wextra -std=c99 -g"

if [ "$DEBUG_MODE" = true ]; then
    COMPILE_CMD="$COMPILE_CMD -DDEBUG -O0"
else
    COMPILE_CMD="$COMPILE_CMD -O2"
fi

COMPILE_CMD="$COMPILE_CMD ${FILENAME}.c common.c -o ${FILENAME}"

# 显示编译信息
echo -e "${YELLOW}正在编译 ${FILENAME}.c 和 common.c...${NC}"
if [ "$DEBUG_MODE" = true ]; then
    echo -e "${YELLOW}编译命令: $COMPILE_CMD${NC}"
fi

# 执行编译
$COMPILE_CMD

# 检查编译结果
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ 编译成功! 生成可执行文件: ${FILENAME}${NC}"

    # 自动运行程序
    if [ "$RUN_AFTER_BUILD" = true ]; then
        echo -e "${YELLOW}正在运行程序...${NC}"
        echo "----------------------------------------"
        ./"$FILENAME"
        echo "----------------------------------------"
        echo -e "${GREEN}程序执行完成${NC}"
    else
        echo -e "${GREEN}运行命令: ./${FILENAME}${NC}"
    fi
else
    echo -e "${RED}✗ 编译失败!${NC}"
    exit 1
fi
