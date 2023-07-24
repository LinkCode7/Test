#include "constexpr.h"

int       g_int  = 0;
const int g_int2 = 11;

int get1()
{
    return g_int;
    // 00007FF760A418D2  mov         eax, dword ptr[g_int(07FF760A50434h)]
}
int get2()
{
    return g_int2;
    // 00007FF760A418E2  mov         eax,11
}

TEST(std_constexpr, function)
{
    // 大多数情况下，const不会影响性能，更多的是处于可读性考虑
    // 编译器并不能依据const来优化代码，https://stackoverflow.com/questions/3435026/can-const-correctness-improve-performance
    get1();
    get2();

    std::cout << "fibonacci(10) = " << fibonacci(10) << std::endl;
    // std::cout << "fibonacci(10000) = " << fibonacci(10) << std::endl;

    int size = 10;
    // int arr[size]; // error C2131: 表达式的计算结果不是常数
    int arr[fibonacci(5)] = {0};
}

TEST(std_constexpr, if_statement)
{
    // 编译器会将代码表现为两个重载函数"int print_type_info(int)"及double的形式
    std::cout << "void if_constexpr()" << std::endl;
    std::cout << print_type_info(1) << std::endl;
    std::cout << print_type_info(1.0) << std::endl;
}

TEST(std_const, basic)
{
    // C语言中的const是一个不能被改变的普通变量，会占用存储空间
    // C++中的const一般被看成编译期的常量，不为const分配空间, 只是在编译的时候将值保存在符号表中，并在适当的时候折合在代码中
    // 若加上关键字extern或者取const变量地址，编译器就要为const分配存储空间

    const int size        = 10;
    int       array[size] = {0}; // C语言中error: 编译器不知道编译时的值（数组下标必须明确）

    // const常量引入的初衷是替代#define常量
    const int const_value = 1;

    // int* temp = const_value; // error C2440: “初始化”: 无法从“const int”转换为“int *”
    int* pa1 = (int*)&const_value;             // 传统方式去除const限定
    int* pa2 = const_cast<int*>(&const_value); // 去除const限制

    // 这里直接被替换成常量表达式，不再从地址中取值
    *pa1        = 100;
    int modify1 = const_value; // 1

    *pa2        = 10;
    int modify2 = const_value; // 1
}