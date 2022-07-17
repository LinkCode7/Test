#include "pch.h"
#include <iostream>

using namespace std;
// 判断一个数时候为回文数(121,12321,35653) 
//unsigned char Symmetry(long n)
bool Symmetry(long n)
{
	long i, temp, cout(0);
	i = n; temp = 0;
	//cout << "begin:		i: " << i << endl;
	//cout << "        temp: " << temp << endl;

	//while (i) //不用出现长度问题,将数按高低位掉换
	//{
	//	temp = temp * 10 + i % 10;
	//	i /= 10;

	//	cout << "count:" << cout++  << "i:" << i << endl;
	//	cout << "      " << "temp:" << temp << endl;
	//}

	//cout << "end:		i: " << i << endl;
	//cout << "        temp: " << temp << endl;
	return(temp == n);
}

void algorithm()
{
	Symmetry(12321);
}
