#include "petal.h"

#include <array>
#include <bitset>
#include <initializer_list>

using namespace std;

#pragma warning(disable : 4244)
#pragma warning(disable : 4056)
#pragma warning(disable : 4305)
#pragma warning(disable : 4101)
#pragma warning(disable : 4309)

TEST(TestCpp, petal)
{
    petal1();
    petal2();
}

void petal1()
{
    // 1
    int    x = {5};
    double y{3.14};
    short  quar[5]{2, 4, 6, 8};
    // class A ...

    int* arr = new int[4]{2, 3, 4, 5};

    // {}会检查变量的范围
    char c1 = 1.57e27;
    char c2 = 459585821;

    char c3{66};
    char c4{66};

    // 2
    vector<int> vec1(10);           // 10个未初始化的值
    vector<int> vec2{10};           // 包含一个元素：10
    vector<int> vec{1, 2, 3, 4, 5}; // 初始化5（N）个元素

    // 3
    double total = sum({2.0, 3.1, 4}); // 调用者可以这么写

    //// 4 auto
    // auto maton = 112; // type:int
    // auto pt = &maton; // type:int*
    // double fm(double, int);
    // auto pf = fm; // type: double (*)(double,int)
    //// auto简化迭代器声明

    // 5 decltype
    // 将变量的类型声明为表达式指定的类型
    decltype(x)      yy; // 让yy的类型与x相同
    double           xx;
    int              n;
    decltype(xx * n) q;  // q same type as x*n,i.e,double
    decltype(&xx)    pd; // pd same as &x,i.e,double*

    // decltype在定义模板时非常有用
    // useful(char('a'), short(5)); // result为int类型

    int             j  = 3;
    int&            k  = j;
    const int&      nn = j;
    decltype(nn)    i1 = 5; // const int&，必须初始化
    decltype(j)     i2;     // int
    decltype((j))   i3 = j; // int&，必须初始化
    decltype(k + 1) i4;     // int

    // 6 函数返回类型后置声明（在函数名后、且在参数列表后指定返回类型）
    double f1(double, int);         // traditional syntax
    auto   f2(double, int)->double; // return type: double

    // eff(3.14, 5); // 编译器遇到eff参数列表时，T和U还不在作用域内，因此要在参数列表后使用decltype

    // 7 模板别名：using =
    using itType = std::vector<std::string>::iterator; // 此处类似于typedef，简化冗长代码

    // arr12<double> a1; // std::array<double, 12> a1;
    // arr12<std::string> a2; // std::array<std::string, 12> a2;

    // 8 nullptr

    // 9 智能指针（所有智能指针都能与移动语义协同工作）

    // 10 关于异常的补丁（摒弃void fun() throw的异常规范，添加noexcept关键字：声明函数不会引发异常）

    // 11 枚举
    enum Old1
    {
        yes,
        no,
        mabe
    };
    // enum Old2 {yes,oh}; // error C2365: “Base::yes”: 重定义

    enum class New1
    {
        never,
        sometimes,
        often,
        always
    };
    enum class New2
    {
        never,
        ok
    }; // 可以同名
    enum struct New3
    {
        never,
        sometimes,
        often,
        always
    };
}

void petal2()
{
    // 1 对类的修改

    // 1.1 显式转换运算符
    /*Plebe a, b; //zh
    a = 5;
    b = 0.5;
    b = Plebe(0.5);*/

    // 1.2 类内初始化成员变量

    // 2 模板和STL方面的修改

    // 2.1 基于范围的for循环（对于内置数组和实现begin()、end()方法的类和STL容器，可以：）
    double prices[5] = {1, 2, 3, 4, 5};
    for (auto x : prices) // 只读最好加const: for (const auto TypeName : Type)
    {
        std::cout << x << std::endl;
    }

    for (auto& x : prices) // 需要修改
    {
        x = std::rand();
    }

    // 2.2 新的STL容器

    // 单向链表
    // forward_list,unordered_map,unordered_multimap,unordered_set,unordered_multiset

    std::array<int, 10> arr;

    // 2.3 新的STL方法

    // cbegin(),cend(),		crbegin()和crend()是rbegin()、rend()的const版本

    // 2.4 valarray升级（由于C++11新添的两个方法begin()和end()接受valarray做参数，使valarray可以用基于范围的for循环）

    // 2.5 摒弃 export关键字

    // 2.6 尖括号：声明嵌套模板时可以不分开尖括号 vector<list<int>> data;

    // 3 右值引用
}

void petal3()
{
    std::bitset<68> bits(1);
    std::cout << bits.to_string() << std::endl;
}