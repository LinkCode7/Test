#include "std_bind.h"

#include <array>
#include <functional>

using namespace std;

void test_bind()
{
    _test_bind();

    test_placeholders();
    test_placeholders2();
}

double my_divide(double x, double y)
{
    return x / y;
}
std::ostream& print(std::ostream& os, const std::string& str, char ch)
{
    os << str << ch;
    return os;
}

void _test_bind()
{
    // 绑定普通函数
    auto fun1 = std::bind(my_divide, std::placeholders::_1, 2);
    std::cout << fun1(1) << std::endl; // 1 / 2

    // 绑定成员函数
    Params params;
    auto   fun2 = std::bind(&Params::Print, &params, std::placeholders::_1, 20);
    fun2(2);

    auto fun3 = std::bind(params, std::placeholders::_1, 30);
    fun3(3);

    // 对有些绑定的参数希望以引用的方式传递
    {
        vector<string> words{"helo", "world", "this", "is", "C++11"};
        ostringstream  os;
        char           ch = ' ';
        for_each(words.begin(), words.end(), [&os, ch](const string& str) { os << str << ch; });
        cout << os.str() << endl;

        ostringstream os1;
        // ostream不能拷贝，若希望传递给bind一个对象，
        // 而不拷贝它，就必须使用标准库提供的ref函数
        for_each(words.begin(), words.end(), bind(print, std::ref(os1), std::placeholders::_1, ch));
        cout << os1.str() << endl;
    }
}

void test_placeholders()
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    std::replace(s.begin(), s.end(), 8, 88);

    for (int a : s)
    {
        std::cout << a << " ";
    }
    std::cout << '\n';

    // 将所有小于5的数替换为55
    std::replace_if(s.begin(), s.end(), std::bind(std::less<int>(), std::placeholders::_1, 5), 55);

    for (int a : s)
    {
        std::cout << a << " ";
    }
    std::cout << '\n';
}

// auto f = std::bind(function, std::placeholders::_n);
// 代表：placeholders处的形参被占位，调用时填入的值是第n个实参
void test_placeholders2()
{
    std::cout << std::endl << ">> test_placeholders2()" << std::endl << std::endl;

    Params1 objParams1;
    auto    f1 = std::bind(objParams1, 1);
    f1();

    auto f2 = std::bind(objParams1, std::placeholders::_1);
    f2(2);

    std::cout << std::endl;
    auto f3 = std::bind(objParams1, std::placeholders::_1);
    f3(3);                // 3
    f3(3, 33);            // 3
    f3(3, 33, 333);       // 3
    f3(3, 33, 333, 3333); // 3

    auto _f3 = std::bind(objParams1, std::placeholders::_2);
    //_f3(3); // error，实参数量不足_2
    _f3(3, 33);            // 33
    _f3(3, 33, 333);       // 33
    _f3(3, 33, 333, 3333); // 33

    std::cout << std::endl << "----------------------------------------------------------" << std::endl;

    Params2 objParams2;
    auto    f4 = std::bind(objParams2, std::placeholders::_1, std::placeholders::_2);
    f4(4, 44);      // left : 4, right : 44
    f4(4, 44, 444); // left : 4, right : 44

    auto f4_2 = std::bind(objParams2, std::placeholders::_2, std::placeholders::_1);
    f4_2(4, 44);      // left : 44, right : 4
    f4_2(4, 44, 444); // left : 44, right : 4

    std::cout << std::endl;

    auto f5 = std::bind(objParams2, 0, 1);
    f5();
    f5(5);

    auto f6 = std::bind(objParams2, std::placeholders::_1, 20);
    f6(6);

    auto f7 = std::bind(objParams2, std::placeholders::_2, 0);
    // f7(7); // error，实参数量不足
    f7(7, 77); // ok
}

void apply(Foo* foo1, Foo* foo2, void (Foo::*fun)())
{
    (foo1->*fun)(); // call fun on the object foo1
    (foo2->*fun)(); // call fun on the object foo2
}
// 指向成员函数的指针
void MemberFunctionPointer()
{
    Foo foo1{1};
    Foo foo2{2};
    apply(&foo1, &foo2, &Foo::f);
    apply(&foo1, &foo2, &Foo::g);
}

void test_function()
{
    // 意义：统一可调用类型
    auto fun = [](int value) { std::cout << value << std::endl; };

    fun(1);

    // 传递闭包对象，隐式转换为 foo* 类型的函数指针值
    _functional(fun);

    // std::function 包装了一个返回值为 int, 参数为 int 的函数
    std::function<int(int)> func = _foo2;

    int                     important = 10;
    std::function<int(int)> func2     = [&](int value) -> int { return 1 + value + important; };

    std::cout << func(10) << std::endl;
    std::cout << func2(10) << std::endl;
}
