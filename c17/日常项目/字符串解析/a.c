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
    int16 inputChar; // gechar 有可能返回负数,int8 装不下,所以是int16
    uint64 expandNumber; // 这个数理论上有可能无限大,但是是单调递增的
    uint8 currentStatus; // 这个数只有会1/0
    inputChar = expandNumber = currentStatus = 0; // 初始化

    printf("请输入一个以形如A{3B}的字符串, ctrl+Z/D结束程序: \n");
    printf("User> "); // 模拟 Linux 终端
    fflush(stdout); // 强制将标准输出缓冲区中的数据立即写入终端

    while ( (inputChar = (int16)getchar()) != EOF) // 循环读取字符,直到遇到文件结束符 (Ctrl+D 或 Ctrl+Z)
    {
        if (inputChar == '\n') // 换行说明用户输入完一行,重置所有状态
        {
            printf("\n\nUser> ");
            fflush(stdout);
            expandNumber = 0; // 清空遗留的计数器
            currentStatus = 0; // 强制退出花括号状态,防止上一行未闭合影响下一行
            continue; // 开始下一轮循环
        }

        if (currentStatus == 0) // 状态 0:在花括号外部(正常字符模式)
        {
            if (inputChar == '{') {
                currentStatus = 1; // 遇到 '{',状态切换至:进入花括号内部
                expandNumber = 0; // 确保进入新括号时,计数器是清零状态
            }
            else { putchar(inputChar); } // 不是 '{' 的普通字符,直接原样输出到屏幕
        } 
        else // 状态 1:在花括号内部(解析指令模式)
        {
            if ( isdigit(inputChar) ) { expandNumber = expandNumber * 10 + (uint64)(inputChar - '0'); }
            // 遇到数字:利用十进制移位原理,将单个字符拼成多位整数 (如 '1' '2' -> 12)
            else if (inputChar == '}') { currentStatus = 0; } // 遇到 '}',状态切换至:回到花括号外部
            else 
            {
                if (expandNumber > 0) // 既不是数字也不是 '}',说明遇到了需要被重复的目标字符(例如 {3B} 中的 'B')
                {
                    for (uint64 k = 0; k < expandNumber; k++) { putchar(inputChar); } 
                    // 根据累计好的 expandNumber 次数,循环打印该目标字符
                    expandNumber = 0; // 打印完成后必须清零,以支持形如 {3A2B} 的连续解析
                }
                else { putchar(inputChar); } // 边缘情况:如果计数器是0(如输入了 {B} 或 {0B}),则按常规打印一次
            }
        }
    }

    printf("\n[程序已结束]\n");
    return 0;
}
