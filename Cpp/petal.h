#pragma once



void petal1();
void petal2();
void petal3();



double sum(std::initializer_list<double> il)
{
	double total{ 0 };
	for (auto p = il.begin(); p != il.end(); p++)
	{
		total += *p;
	}
	return total;
}

template<typename T, typename U>
decltype(T*U) useful(T t, U u)
{
	decltype(T*U) re(t*u);
	return re;
}

template<typename T, typename U>
auto eff(T t, U u) -> decltype(T*U)
{
	// ...
}

template<typename T>
using arr12 = std::array<T, 12>; // template for multiple aliases: 具体化模板<T, int>










class Plebe
{
	Plebe(int);					// automatic int-to-plete conversion
	explicit Plebe(double);		// requires explicit use
};

class Session
{
	int num = 0;
	double pi{ 3.14 }; // 不能使用小括号初始化，这等同于构造

public:
	Session(int n, double p) :num(n), pi(p) {} // 构造函数的成员初始化列表，将会覆盖类内初始化的值
};