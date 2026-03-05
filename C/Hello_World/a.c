#include <assert.h>   // 调试断言
#include <ctype.h>    // 字符分类与转换
#include <errno.h>    // 错误码
#include <float.h>    // 浮点数极限与特性
#include <limits.h>   // 整数极限
#include <locale.h>   // 本地化设置
#include <math.h>     // 数学函数
#include <setjmp.h>   // 非局部跳转
#include <signal.h>   // 信号处理
#include <stdarg.h>   // 可变参数列表
#include <stddef.h>   // 常用类型与宏 (如 size_t)
#include <stdio.h>    // 标准输入输出
#include <stdlib.h>   // 通用工具 (内存分配、程序控制等)
#include <string.h>   // 字符串与内存操作
#include <time.h>     // 时间与日期
#include <iso646.h>   // 运算符替代拼写 (如 and, or)
#include <wchar.h>    // 宽字符处理
#include <wctype.h>   // 宽字符分类与转换
#include <complex.h>  // 复数算术
#include <fenv.h>     // 浮点数环境
#include <inttypes.h> // 精确位宽整数的格式化转换
#include <stdbool.h>  // 布尔类型 (bool, true, false)
#include <stdint.h>   // 精确位宽整数类型 (如 int32_t)
#include <tgmath.h>   // 泛型数学宏
#include <stdalign.h>    // 内存对齐 (alignas, alignof)
#include <stdatomic.h>   // 原子操作
#include <stdnoreturn.h> // 不返回函数声明 (noreturn)
#include <threads.h>     // 多线程支持
#include <uchar.h>       // Unicode 字符类型
// ... 宏定义/类型别名 ...
#define FMT_INT64   PRId64
#define FMT_UINT64  PRIu64
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
    printf("Hello,World!");
}



