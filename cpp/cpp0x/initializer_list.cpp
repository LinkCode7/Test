#include "pch.h"
#include "initializer_list.h"




// ����ʼ���б�ĸ���󶨵������ϣ�����֮Ϊinitializer_list��
// �����캯�������������� ����һ����ʼ���б�
void test_initializer_list()
{
	int arr[3] = { 1, 2, 3 };
	std::vector<int> vec = { 1, 2, 3, };

	Fool foo1(1, 2);
	Fool foo2{ 1, 2 };

	MagicFool magicFoo1 = { 1, 2, 3 };
	MagicFool magicFoo2{ 3,4 };
}