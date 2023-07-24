#include "base.h"

#include <functional>

using namespace std;

const char* getCharacter()
{
    return "a";
}

////////////////////////////////////////////////////////////////////////////////////
int tt(int t)
{
    return 0;
}

struct MyStruct
{
    int a;

    MyStruct(int aa) : a(aa) {}
    MyStruct(const MyStruct& oth) { a = oth.a; }
};

void wulusaiyi()
{
    MyStruct* p1 = new MyStruct(1);
    MyStruct* p2 = new MyStruct(2);
    *p2          = *p1;

    delete p1;
    delete p2;
}

class Base
{
public:
    void foo(int x) { cout << "Base foo()" << endl; }
};

class Derived : public Base
{
public:
    void foo(int pd) { cout << "Derived foo()" << endl; }
};

class AA
{
public:
    AA() { m_i = 0; }
    virtual ~AA() { cout << "~A()" << endl; }

    int m_i;
};
class BB : public AA
{
public:
    BB() { m_ii = 1; }
    ~BB() { cout << "~B()" << endl; }

    int m_ii;
};

TEST(TestCpp, base)
{
    return;

    AA* pA = new BB;
    delete pA;

    Base* pd = new Derived;
    pd->foo(10);
    delete pd;

    wulusaiyi();

    int a(0);
    int b = ++a + tt(a++);

    string str3;
    str3 = getCharacter();
    wprintf(L"%p\n", str3.c_str());
    string str1 = getCharacter();
    wprintf(L"%p\n", str1.c_str());
    string str2(getCharacter());
    wprintf(L"%p\n", str2.c_str());

    std::function<int(int)> func = [](int i) { return i; };

    C<int(int)> c([](int a) { return a; });

    cout << func(111) << endl;
    cout << c(11) << endl;

    std::function<int(int, int)> f1 = [](int a, int b) { return a + b; };

    std::function<string(int, string s)> f2 = [](int a, string b) { return b; };

    auto re1 = f1(2, 5);
    auto re2 = f2(1, string("aaa"));
}
