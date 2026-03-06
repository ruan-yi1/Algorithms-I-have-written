#include <assert.h>    // 调试断言
#include <ctype.h>     // 字符分类与转换
#include <errno.h>     // 错误码
#include <float.h>     // 浮点数极限与特性
#include <limits.h>    // 整数极限
#include <locale.h>    // 本地化设置
#include <math.h>      // 数学函数
#include <setjmp.h>    // 非局部跳转
#include <signal.h>    // 信号处理
#include <stdarg.h>    // 可变参数列表
#include <stddef.h>    // 常用类型与宏 (如 size_t)
#include <stdio.h>     // 标准输入输出
#include <stdlib.h>    // 通用工具 (内存分配、程序控制等)
#include <string.h>    // 字符串与内存操作
#include <time.h>      // 时间与日期
#include <iso646.h>    // 运算符替代拼写 (如 and, or)
#include <wchar.h>     // 宽字符处理
#include <wctype.h>    // 宽字符分类与转换
#include <complex.h>   // 复数算术
#include <fenv.h>      // 浮点数环境
#include <inttypes.h>  // 精确位宽整数的格式化转换
#include <stdbool.h>   // 布尔类型 (bool, true, false)
#include <stdint.h>    // 精确位宽整数类型 (如 int32_t)
#include <tgmath.h>    // 泛型数学宏
#include <stdalign.h>  // 内存对齐 (alignas, alignof)
#include <stdatomic.h> // 原子操作
#include <stdnoreturn.h>// 不返回函数声明 (noreturn)
#include <threads.h>   // 多线程支持
#include <uchar.h>     // Unicode 字符类型

// ... 宏定义/类型别名 ...
#define FMT_INT64  PRId64
#define FMT_UINT64 PRIu64

typedef uint8_t uint8;          // 0 到 255
typedef int8_t int8;            // -128 到 127
typedef uint16_t uint16;        // 0 到 65,535
typedef int16_t int16;          // -32,768 到 32,767
typedef uint32_t uint32;        // 0 到 2^{32}-1
typedef int32_t int32;          // -2^{31} 到 2^{31}-1
typedef uint64_t uint64;        // 0 到 2^{64}-1
typedef int64_t int64;          // -2^{63} 到 2^{63}-1
typedef __int128 int128;        // -2^{127} dao 2^{127}-1
typedef unsigned __int128 uint128; // 0 dao 2^{128}

int main(void)
{
    uint64 numberLines, numberCharacters, numberWords;
    uint8 incompleteRow, inWord;
    int16 lastCharacterRead, currentCharacter; 

    currentCharacter = numberCharacters = numberLines = numberWords = inWord = incompleteRow = 0;
    lastCharacterRead = '\n';

    printf("请输入内容(Ctrl+D/Z 结束程序)\n");
    
    while ( (currentCharacter = (int16)getchar() ) != EOF)
    {
        numberCharacters++; 

        if (currentCharacter == '\n') {
            numberLines++;
        } 

        if (!isspace((uint16)currentCharacter)) 
        {
            numberWords += !inWord; 
            inWord = 1;
        } else {
            inWord = 0;
        }

        lastCharacterRead = currentCharacter; 
    }

    if (lastCharacterRead != '\n') {
        incompleteRow++;
    } 

    printf("\n--- 统计结果 ---\n");
    printf("字符数 (Characters): %" PRIu64 "\n", numberCharacters);
    printf("单词数 (Words): %" PRIu64 "\n", numberWords);
    printf("完整行数 (Lines): %" PRIu64 "\n", numberLines);
    printf("不完整行 (Incomplete rows): %hhu\n", incompleteRow);
}

/*
 * - uint64 (numberLines, numberCharacters, numberWords): 
 * 实际上是从当一个计数器的作用，只会增加不会减少，而且为了一次能统计更多，所以直接规定类型为 uint64。
 * - uint8 (incompleteRow, inWord): 
 * 实际上只会是 1/0，所以直接给最小类型 uint8。
 * - int16 (lastCharacterRead, currentCharacter): 
 * 因为最后一个返回的字符一定在 -1 到 255，所以直接上 int16。
 *
 * - 字符计数: 无论输入什么，字符数量每次循环都加 1。
 * - 行数统计: 如果是换行符则行数加 1。
 * - 单词统计与安全检查: isspace 判断负数可能会导致未定义行为，因为循环已经确保 EOF 不会传入，
 * 所以将 currentCharacter 强行转换成无符号。并且因为 ! 运算严格返回 1/0，所以可以放心进行算术累加：
 * 如果不在单词内 (!0 变成 1)，计数+1；如果在单词内 (!1 变成 0)，加0。
 * 每次循环记录最后一个字符 lastCharacterRead。循环结束后，判断最后一个字符是否为不完整行。
 *
 * 我不知道我为什么要这么在意这些个不同字节的整型,反正内存占用也没有变,类型转换在ASM层面也是零成本的(貌似)
 * 虽然没什么用甚至有可能有副作用,但是这很有意思不是吗,就当训练我的思维能力了吧
 */
