#include "pch.h"
#include "initializer_list.h"




// 将初始化列表的概念绑定到类型上，并称之为initializer_list，
// 允许构造函数及其它函数像 参数一样初始化列表
void test_initializer_list()
{
	int arr[3] = { 1, 2, 3 };
	std::vector<int> vec = { 1, 2, 3, };

	Fool foo1(1, 2);
	Fool foo2{ 1, 2 };

	MagicFool magicFoo1 = { 1, 2, 3 };
	MagicFool magicFoo2{ 3,4 };
}