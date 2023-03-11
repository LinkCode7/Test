#pragma once
//#include <sstream>



void _test_bind();

void test_placeholders();
void test_placeholders2();

void test_function();



class Params1
{
public:
	Params1()
	{
		std::cout << "Params1()" << std::endl;

	}
	void operator()(int value)
	{
		std::cout << "void operator(int value) value : " << value << std::endl;
	}
};

class Params2
{
public:
	Params2()
	{
		std::cout << "Params2()" << std::endl;

	}
	void operator()(int left, int right)
	{
		std::cout << "void operator()(int left, int right) left : " << left << ", right : " << right << std::endl;
	}
};


class Params
{
public:
	Params()
	{
		std::cout << "Params()" << std::endl;

	}
	void operator()(int left, int right)
	{
		std::cout << "void operator()(int left, int right) left : " << left << ", right : " << right << std::endl;
	}

	void Print(int left, int right)
	{
		std::cout << "void Print()(int left, int right) left : " << left << ", right : " << right << std::endl;
	}

	std::ostream& PrintStream(std::ostream& os, const std::string& str, char ch)
	{
		std::cout << "std::ostream& Print(std::ostream& os, const string& str, char ch) os, str : ";
		std::cout << str << ", ch : " << ch << std::endl;
		os << str << ch;
		return os;
	}
};

struct Foo
{
	int value;
	void f() { std::cout << "f(" << this->value << ")\n"; }
	void g() { std::cout << "g(" << this->value << ")\n"; }
};









using _foo1 = void(int); // 定义函数类型
void _functional(_foo1 f)
{
	// 定义在参数列表中的函数类型 foo 被视为退化后的函数指针类型 foo*
	f(1); // 通过函数指针调用函数
}

int _foo2(int param)
{
	return param;
}