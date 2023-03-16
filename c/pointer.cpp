#include "pch.h"
using namespace std;



void swap1(int* a,int* b)
{
	if (!a || !b)
		return;
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap2(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//////////////////////////////////////////////////////////

void testPoint()
{
	int x = 1;
	int y = 2;
	int a = 11;
	int b = 22;

	swap1(nullptr, nullptr);
	swap1(&a, &b);
	swap2(x,y);
	
	cout << "(a,b) " << a << "," << b << endl;
	cout << "(x,y) " << x << "," << y << endl;
}