#include "fibonacci_sequence.h"

using namespace std;

// 0 1 1 2 3 5 8 13 21 34 ...
void Fibonacci::generate(double n)
{
    a = 0;
    b = 1;
    for (int i = 1; i <= n - 2; i++)
    {
        c = a + b;
        m_store.push_back(c);
        a = b;
        b = c;
    }
}

double Fibonacci::getValueByIndex(double n)
{
    // Check

    // General formula
    // F(n) = (1/√5) * { [(1+√5)/2]^n - [(1-√5)/2]^n }
    return ((pow((1 + sqrt(5)) / 2, n)) / sqrt(5)) - ((pow((1 - sqrt(5)) / 2, n)) / sqrt(5));
}

bool isFibonacci(double number)
{
    return true;
}

void Fibonacci::print(std::string separator)
{
    if (m_store.empty())
        return;
    for (const auto& n : m_store)
    {
        cout << n << separator;
    }
}

/////////////////////////////////////////////////////////////////

double fun(double a, double b)
{ // Division
    return (a - (int)(a / b)) * b;
}

/////////////////////////////////////////////////////////////////

void testAlgorithm()
{
    // 1
    double r1      = 5 / 2;
    double r2      = 5 / 2.0;
    double result1 = 5 % 2;
    double result2 = 2 % 5;
    double result3 = fun(2, 5);

    // 2
    cout << "Hello world! Fibonacci series" << endl;
    cout << "Enter number of items you need in the series: ";
    int n;
    cin >> n;

    Fibonacci fibonacci;
    fibonacci.generate(n);

    cout << endl;
    for (auto i = 0; i < n; ++i)
    {
        cout << fibonacci.getValueByIndex(i) << " ";
    }
}

// 相关面试题：
// 一个台阶总共有n级，如果一次可以跳1级，也可以跳2级。求总共有 多少总跳法?
/*
解题方法：不要怕难，怕没见过。写出n等于1，2，3，4，5时的跳法数量，总结规律

首先我们考虑最简单的情况。。。再讨论一般情况。
把n 级台阶时的跳法看成是关于 n 的函数f(n),
当n>2 时，第一次跳就有两种不同的选择：
一种是第一次只跳1 级，此时跳法数目等于后面剩下的n-1 级台阶的跳法数目，即为f(n-1)；
另一种是第一次跳2 级，此时跳法数目等于后面剩下的n-2 级台阶的跳法数目，即为f(n-2)。
因此n 级台阶时的不同跳法的总数f(n) = f(n-1) + f(n-2)。
我们把上面的分析用一个公式总结如下：
f(n) =  1  (n=1)
f(n) =  2  (n=2)
f(n) =f(n-1) + (f-2)  (n>2)
分析到这里，相信很多人都能看出这就是我们熟悉的Fibonacci 序列。(O(n))

*/
