#include "pch.h"
#include "Fibonacci.h"

using namespace std;

// 0 1 1 2 3 5 8 13 21 34 ...
void Fibonacci::generate(double n)
{
	a = 0; b = 1;
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
	// F(n) = (1/��5) * { [(1+��5)/2]^n - [(1-��5)/2]^n }
	return ((pow((1 + sqrt(5)) / 2, n)) / sqrt(5)) - ((pow((1 - sqrt(5)) / 2, n)) / sqrt(5));
}

bool isFibonacci(double number)
{	
	return true;
}

void Fibonacci::print(std::string separator)
{
	if (m_store.empty()) return;
	for (const auto& n : m_store)
	{
		cout << n << separator;
	}
}




/////////////////////////////////////////////////////////////////

double fun(double a, double b)
{// Division
	return (a - (int)(a / b))*b;
}

/////////////////////////////////////////////////////////////////

void testAlgorithm()
{
	// 1
	double r1 = 5 / 2;
	double r2 = 5 / 2.0;
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
	for (auto i = 0; i<n; ++i)
	{
		cout << fibonacci.getValueByIndex(i) << " ";
	}
}

// ��������⣺
// һ��̨���ܹ���n�������һ�ο�����1����Ҳ������2�������ܹ��� ����������?
/*
���ⷽ������Ҫ���ѣ���û������д��n����1��2��3��4��5ʱ�������������ܽ����

�������ǿ�����򵥵����������������һ�������
��n ��̨��ʱ�����������ǹ��� n �ĺ���f(n),
��n>2 ʱ����һ�����������ֲ�ͬ��ѡ��
һ���ǵ�һ��ֻ��1 ������ʱ������Ŀ���ں���ʣ�µ�n-1 ��̨�׵�������Ŀ����Ϊf(n-1)��
��һ���ǵ�һ����2 ������ʱ������Ŀ���ں���ʣ�µ�n-2 ��̨�׵�������Ŀ����Ϊf(n-2)��
���n ��̨��ʱ�Ĳ�ͬ����������f(n) = f(n-1) + f(n-2)��
���ǰ�����ķ�����һ����ʽ�ܽ����£�
f(n) =  1  (n=1)
f(n) =  2  (n=2)
f(n) =f(n-1) + (f-2)  (n>2)
������������źܶ��˶��ܿ��������������Ϥ��Fibonacci ���С�(O(n))

*/


